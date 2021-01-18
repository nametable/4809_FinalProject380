# BT KB Remote
## Hardware
 - Uno Wifi Rev2
 - Extra buttons and leds supported
## Software Dependencies
 1. Python libraries:
    ```
    PyBluez keyboard 
    ```
 2. Arduino Software (with Uno Wifi Rev2 Board support)
 3. Arduino ESP32 support from https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json (add to additional boards in preferences)
 4. `make`, `cmake`, '`dfu-programmer`

## Installation #
 1. Program WifiNina chip with [SerialToSerialBT example](https://github.com/espressif/arduino-esp32/blob/master/libraries/BluetoothSerial/examples/SerialToSerialBT/SerialToSerialBT.ino), replacing `ESP32test` with the name you want. In order to flash to the wifi chip, use WifiNINA SerialNinaPassthrough example.
     - Use  `--before no_reset` instead of `--before default_reset` on the `esptool` command that the Arduino IDE uses.
 2. Configure (runs cmake)
    ```bash
    ./configure.sh
    ```

 3. Build binaries for 4809 and 32u4
    ```bash
    ./build.sh
    ```
 4. Build Android app (BTKBRemote) with Android Studio

## Flashing
 ### 4809
 1. Modify `flash_4809.sh` to use your avrdude path and device (eg `/dev/ttyACM1`)
 2. Run flashing script
    ```bash
    ./flash_4809.sh
    ```
### 32u4
 ⚠️ Warning ⚠️ - This operation will erase the original firmware on the Atmega32u4 - which may be difficult to obtain to completely restore your Board. Partial restore can be done with `restore_32u4.sh` by putting `medbgupdi.hex` into `32u4` folder (obtain from Atmel Studio)
 1. Put atmega32u4 into DFU mode:
    - Connect PE2 test point to GND
    - While PE2 is connected to GND, connect RST test point to GND and release
 2. Run flashing script
    ```bash
    ./flash_32u4.sh
    ```
## Usage
 1. Plug Uno Wifi Rev2 into Computer or other USB host that recognizes USB-HID
 2. Pair Android phone to device with bluetooth settings
 3. Open Android app (BTKBRemote) and use, typing in text and sending
 4. Buttons (if present)
   - 2 buttons which inject text (PD0, PD1)
   - 1 button to slow down transmission (PD2)

## Performance Testing
 1. Simple time between keypresses test can be found in `tests/performance_test.py`
     - Sample data -> [performance_data.xlsx](tests/performance_data.xlsx)

## External source
 - USB Protocol Implementation for 32u4 taken from https://github.com/kmani314/ATMega32u4-HID-Keyboard and modified