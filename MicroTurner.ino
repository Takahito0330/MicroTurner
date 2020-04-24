/**
   @file MicroTurner.ino
   @brief BLuetooth譜めくりフットペダルのmicro:bit用プログラム
   @author Takahito Suzuki
   @date 2020.4.19
*/

#include <SPI.h>
#include <BLEHIDPeripheral.h>
#include <BLEKeyboard.h>
#include "MicrobitLED.h"

//#define ANDROID_CENTRAL

//! 送出先デバイスのOS定義
enum TARGET_TYPE
{
  WINDOWS,
  MAC
};
enum TARGET_TYPE target = MAC;
// ページアップとページダウン信号
uint8_t signal_up, signal_down;

BLEHIDPeripheral bleHIDPeripheral = BLEHIDPeripheral();
BLEKeyboard bleKeyboard;

void signal_config()
{
  // OSによって送出信号を切り替え
  switch (target)
  {
    case WINDOWS:
      Serial.println("Windows Mode");
      signal_up = 75;
      signal_down = 78;
      break;
    case MAC:
      Serial.println("Mac Mode");
      signal_up = 82;
      signal_down = 81;
      break;
    default:
      Serial.println("UNKNOWN Mode");
      signal_up = 0;
      signal_down = 0;
      break;
  }
}

void setup()
{
  Serial.begin(9600);
  // clear bond store data
  bleHIDPeripheral.clearBondStoreData();

#ifdef ANDROID_CENTRAL
  bleHIDPeripheral.setReportIdOffset(1);
#endif

  bleHIDPeripheral.setLocalName("HID Keyboard");
  bleHIDPeripheral.setDeviceName("micro-Turn");
  bleHIDPeripheral.addHID(bleKeyboard);
  bleHIDPeripheral.begin();

  led_init();
  signal_config();

  pinMode(PIN_BUTTON_A, INPUT);
  pinMode(PIN_BUTTON_B, INPUT);

  pinMode(PIN_A0, INPUT);
  pinMode(PIN_A1, INPUT);

  Serial.println(F("BLE HID Keyboard"));
}

void loop()
{
  BLECentral central = bleHIDPeripheral.central();
  int _code = -1;

  show_icon(DISCONNECT);

  if (central)
  {
    // central connected to peripheral
    Serial.print(F("Connected to central: "));
    Serial.println(central.address());

    while (central.connected())
    {
      show_icon(CONNECT);

      if (!digitalRead(PIN_BUTTON_A))
      {
        Serial.println("PUSH A");
        _code = signal_up;
      }
      if (!digitalRead(PIN_BUTTON_B))
      {
        Serial.println("PUSH B");
        _code = signal_down;
      }
      if (!digitalRead(PIN_A0))
      {
        Serial.println("PUSH PIN0");
        _code = signal_up;
      }
      if (!digitalRead(PIN_A1))
      {
        Serial.println("PUSH PIN1");
        _code = signal_down;
      }

      if (_code >= 0)
      {
        bleKeyboard.press(_code);
        bleKeyboard.releaseAll();

        Serial.print("Send code: ");
        Serial.println(_code);
        _code = -1;
        delay(100);
      }
    }

    // central disconnected
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
