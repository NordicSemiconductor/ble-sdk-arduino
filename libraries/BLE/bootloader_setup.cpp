#include <avr/wdt.h>
#include <EEPROM.h>
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
    crc ^= data_in[i];
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

void bootloader_jump(aci_state_t *state)
{
  Serial.println("Jumping to bootloader");
  delay(100);

  /* Wait until ready line goes low before jump */
  while (digitalRead(state->aci_pins.rdyn_pin));

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
    uint16_t adv_interval, uint8_t *pipes, uint8_t n_pipes)
{
  const uint16_t eeprom_base_addr = E2END - BOOTLOADER_EEPROM_SIZE;

  uint8_t readback_buf;
  uint16_t addr;
  uint16_t crc_eeprom;
  uint16_t crc_readback;

  /* Data to be stored, if it is found to be different from what
   * is stored already
  */
  uint8_t valid_app = 1;
  uint8_t valid_ble = 1;
  uint8_t *p = (uint8_t *) &(state->aci_pins);
  uint8_t timeout_h = (uint8_t) conn_timeout >> 8;
  uint8_t timeout_l = (uint8_t) conn_timeout >> 0;
  uint8_t interval_h = (uint8_t) adv_interval >> 8;
  uint8_t interval_l = (uint8_t) adv_interval >> 0;
  uint16_t crc_local;

  /* Length of the data to be stored, excluding CRC */
  uint8_t len = 2 + sizeof(aci_pins_t) + 1 + sizeof(pipes) + 4;

  /* Compute CRC16 for our data */
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
   * everything works out okay
   */
  addr = eeprom_base_addr + len;
  crc_eeprom = (uint16_t) EEPROM.read(addr++);
  crc_eeprom |= (uint16_t) (EEPROM.read(addr) << 8);

  /* If the two CRC values do not match, we proceed with updating the EEPROM */
  if (crc_local != crc_eeprom)
  {
    Serial.println(F("CRC does not match EEPROM. Writing new data."));

    addr = eeprom_base_addr;
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

    EEPROM.write(addr++, timeout_l);
    EEPROM.write(addr++, timeout_h);
    EEPROM.write(addr++, interval_l);
    EEPROM.write(addr++, interval_h);
    EEPROM.write(addr++, (uint8_t) crc_local);
    EEPROM.write(addr++, (uint8_t) (crc_local >> 8));

    /* Because EEPROM is susceptible to wear, we read the data back and
     * compute a CRC16 for the data actually in EEPROM to compare with
     * the CRC already in EEPROM.
     */
    addr = eeprom_base_addr;
    readback_buf = EEPROM.read(addr++);
    crc_readback = crc_16_ccitt(0xFFFF, &readback_buf, 1);
    for (; addr < eeprom_base_addr + len; addr++)
    {
      readback_buf = EEPROM.read(addr);
      crc_readback = crc_16_ccitt(crc_readback, &readback_buf, 1);
    }

    crc_eeprom = (uint16_t) EEPROM.read(addr++);
    crc_eeprom |= (uint16_t) (EEPROM.read(addr) << 8);


    return crc_eeprom == crc_readback;
  }
  else
  {
    /* Computed CRC matched EEPROM CRC. No write necessary */
    return true;
  }
}
