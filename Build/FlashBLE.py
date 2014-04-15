import os
import commands
import subprocess

print "Flashing all BLE examples"

Our_dir = os.getcwd() # get current directory

if "ARDUINO_DIR" in os.environ:

    #Find out a way to use the variable ARDUINO_DIR, as it is set now
    #Right now it has to be relative in order for the makefile to work
    #BLE_DIR = os.environ.get('ARDUINO_DIR')+"/libraries/BLE"
    BLE_DIR = "/cygdrive/c/Arduino/libraries/BLE"
    #BLE_EXAMPLES_DIR = "libraries/BLE/examples/ble_A_Hello_World_Program"
    BLE_EXAMPLES_DIR = BLE_DIR+"/examples"
    print "BLE_DIR=%s" %BLE_DIR
    print "BLE_EXAMPLES_DIR=%s" %BLE_EXAMPLES_DIR
    os.chdir(BLE_EXAMPLES_DIR)
    BLE_FOLDERS = commands.getoutput('ls')
    LIST_EXAMPLES=BLE_FOLDERS.split()
    print "====================", "\nCompiling each example using the ARDMK_FILE"
    for element in LIST_EXAMPLES:
        print "\n\n\nChange directory:"
        OBJ_EXAMPLE=BLE_EXAMPLES_DIR+"/"+element
        print OBJ_EXAMPLE
        os.chdir(OBJ_EXAMPLE)
        print "make upload"
        return_val=subprocess.call(["make", "upload"])
        if return_val == 0:
             print "------------->   Successful flashing   <-------------"
        else:
             print "xxxxxxxxxxx   Error while flashing    xxxxxxxxxxxxxx"
    
    print "===================="
    
    print "\nGo back to our folder %s" %Our_dir
    os.chdir(Our_dir)
else:
    print "Environmental variable ARDUINO_DIR not declared."
    print "Python script unable to run."