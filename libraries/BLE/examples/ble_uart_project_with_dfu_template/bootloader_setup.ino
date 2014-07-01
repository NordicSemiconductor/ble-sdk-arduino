#include <avr/wdt.h>
#include "bootloader_setup.h"

/* This variable is put in .noinit which means it is not initialized
 * to zero during startup.
 */
uint16_t boot_key __attribute__ ((section (".noinit")));

/* Calculate CRC16 */
static uint16_t crc_16_ccitt(uint16_t crc, uint8_t * data_in, uint16_t len)
{
  uint16_t i;

  for(i = 0; i < len; i++)
  {
    crc  = (unsigned char)(crc >> 8) | (crc << 8);
    crc ^= pgm_read_byte(&data_in[i]);
    crc ^= (unsigned char)(crc & 0xff) >> 4;
    crc ^= (crc << 8) << 4;
    crc ^= ((crc & 0xff) << 4) << 1;
  }

  return crc;
}

void bootloader_jump_check (void)
{
  uint8_t wdt_flag = MCUSR & (1 << WDRF);

  MCUSR &= ~(1 << WDRF);
  wdt_disable();

  if (wdt_flag && (boot_key == BOOTLOADER_KEY)) {
    boot_key = 0;

    ((void (*)(void)) BOOTLOADER_START_ADDR) ();
  }
}

void bootloader_jump(void)
{
  Serial.println("Jumping to bootloader");
  delay(100);

  if ((aci_state.data_credit_available != aci_state.data_credit_total)) {
    return;
  }

  if (!lib_aci_is_pipe_available(&aci_state,
        PIPE_DEVICE_FIRMWARE_UPDATE_BLE_SERVICE_DFU_PACKET_RX)) {
    return;
  }

  if (!lib_aci_is_pipe_available(&aci_state,
        PIPE_DEVICE_FIRMWARE_UPDATE_BLE_SERVICE_DFU_CONTROL_POINT_TX)) {
    return;
  }

  if (!lib_aci_is_pipe_available(&aci_state,
        PIPE_DEVICE_FIRMWARE_UPDATE_BLE_SERVICE_DFU_CONTROL_POINT_RX_ACK_AUTO)) {
    return;
  }

  /* Wait until ready line goes low before jump */
  while (digitalRead(aci_state.aci_pins.rdyn_pin));

  /* Set the special bootloader key value */
  boot_key = BOOTLOADER_KEY;

  wdt_enable(WDTO_15MS);
  while(1);
}

/* This function collects the data needed for the bootloader to transfer a
 * new application over BLE. It computes the CRC for this data, and writes
 * the data to EEPROM if the computed CRC is different from the one in EEPROM
 * (or if there is no valid CRC in EEPROM at all).
 *
 * Stored is a byte telling the bootloader that BLE config data is in EEPROM,
 * the pin configuration the user has chosen in setup(), the amount of total
 * credit available (current credit must equal total credit before jumping to
 * bootloader, so there is no need to store both), the pipes used for a DFU
 * transfer, found in this example's services.h, the connection timeout and the
 * connection advertisement interval.
 */
bool bootloader_data_store (aci_state_t *state, uint16_t conn_timeout,
    uint16_t adv_interval)
{
  uint8_t i;
  uint8_t addr;
  uint16_t crc_eeprom;
  uint16_t crc_local;

  /* Data to be stored */
  uint8_t valid_app = 1;
  uint8_t valid_ble = 1;
  uint8_t *p = (uint8_t *) &(state->aci_pins);
  uint8_t pipes[] = {
    PIPE_DEVICE_FIRMWARE_UPDATE_BLE_SERVICE_DFU_PACKET_RX,
    PIPE_DEVICE_FIRMWARE_UPDATE_BLE_SERVICE_DFU_CONTROL_POINT_TX,
    PIPE_DEVICE_FIRMWARE_UPDATE_BLE_SERVICE_DFU_CONTROL_POINT_RX_ACK_AUTO};
  uint8_t timeout_h = (uint8_t) conn_timeout >> 8;
  uint8_t timeout_l = (uint8_t) conn_timeout >> 0;
  uint8_t interval_h = (uint8_t) adv_interval >> 8;
  uint8_t interval_l = (uint8_t) adv_interval >> 0;

  /* len = valid app flag + valid data flag + pin struct + credit byte + pipe array +
   * timeout + interval + crc
   */
  uint8_t len = 2 + sizeof(aci_pins_t) + 1 + sizeof(pipes) + 6;

  /* Compute CRC16 */
  crc_local = crc_16_ccitt(0xFFFF, &valid_app, 1);
  crc_local = crc_16_ccitt(crc_local, &valid_ble, 1);
  crc_local = crc_16_ccitt(crc_local, p, sizeof(aci_pins_t));
  crc_local = crc_16_ccitt(crc_local, &(state->data_credit_total), 1);
  crc_local = crc_16_ccitt(crc_local, pipes, sizeof(pipes));
  crc_local = crc_16_ccitt(crc_local, &timeout_l, 1);
  crc_local = crc_16_ccitt(crc_local, &timeout_h, 1);
  crc_local = crc_16_ccitt(crc_local, &interval_l, 1);
  crc_local = crc_16_ccitt(crc_local, &interval_h, 1);

  /* Read previously stored CRC. If no CRC has been stored previously,
   * this will be a garbage number that very probably won't match, so
   * everything works out okay */
  addr = len - 2;
  crc_eeprom = (uint16_t) EEPROM.read(addr++);
  crc_eeprom |= (uint16_t) (EEPROM.read(addr) << 8);

  /* Abort the EEPROM write if the stored CRC matches the one above */
  if (crc_local == crc_eeprom)
  {
    return false;
  }

  Serial.println(F("CRC does not match EEPROM. Writing new data."));

  /* As the computed CRC value does not match the one in EEPROM,
   * we write the data and CRC to EEPROM
   */
  addr = 0;

  EEPROM.write(addr++, valid_app);
  EEPROM.write(addr++, valid_ble);

  for (uint8_t i = 0; i < sizeof(aci_pins_t); i++)
  {
    EEPROM.write(addr++, *((uint8_t *) &(state->aci_pins) + i));
  }

  EEPROM.write(addr++, state->data_credit_total);

  for (uint8_t i = 0; i < sizeof(pipes); i++)
  {
    EEPROM.write(addr++, pipes[i]);
  }

  /* Write connetion timeout */
  EEPROM.write(addr++, timeout_l);
  EEPROM.write(addr++, timeout_h);

  /* Write advertisement interval */
  EEPROM.write(addr++, interval_l);
  EEPROM.write(addr++, interval_h);

  EEPROM.write(addr++, (uint8_t) crc_local);
  EEPROM.write(addr++, (uint8_t) (crc_local >> 8));

  return true;
}
