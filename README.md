# Bluetooth Page-Turner using micro:bit
This is a program for a page-turning foot-switch.

A page-turning signal will be sent to a device (e.g. iPad) by Bluetooth when a button connected to a micro:bit pushed.

## Compiling environment
Arduino IDE was used for compiling. 
Change its setting.

0. Connect a micro:bit to your PC.
1. Open *File->Preferences*, and add the following URL to the field of "additional board manager URL".
    - **https://sandeepmistry.github.io/arduino-nRF5/package_nRF5_boards_index.json**
2. Open *Tools->Board->Board Manager*, 
    and install **Nordic Semiconductor nRF5 based boards**.
3. Select **BBC micro:bit** on *Tools->Board:*.
4. Select **COMxx (BBC micro:bit)** on *Tools->Serial Port*.
5. Select **S130** on *Tools->Softdevice*.

## Dependencies
- BLEPeripheral [https://github.com/sandeepmistry/arduino-BLEPeripheral]
