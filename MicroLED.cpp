#include <SPI.h>
#include <BLEHIDPeripheral.h>
#include <BLEKeyboard.h>
#include "MicrobitLED.h"

const uint8_t max_cols = 9;
const uint8_t max_rows = 3;
const uint8_t cols[max_cols] = {3, 4, 10, 23, 24, 25, 9, 7, 6};
const uint8_t rows[max_rows] = {26, 27, 28};

//! 接続時ビットマップ
const uint8_t bmap_connect[MICROBIT_LED_ROW][MICROBIT_LED_COL] =
{
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1},
  {0, 0, 0, 1, 0},
  {1, 0, 1, 0, 0},
  {0, 1, 0, 0, 0}
};

//! 非接続時ビットマップ
const uint8_t bmap_disconnect[MICROBIT_LED_ROW][MICROBIT_LED_COL] =
{
  {1, 0, 0, 0, 1},
  {0, 1, 0, 1, 0},
  {0, 0, 1, 0, 0},
  {0, 1, 0, 1, 0},
  {1, 0, 0, 0, 1}
};

//! 次ページ信号送出時ビットマップ
const uint8_t bmap_next[MICROBIT_LED_ROW][MICROBIT_LED_COL] =
{
  {0, 0, 1, 0, 0},
  {0, 0, 0, 1, 0},
  {1, 1, 1, 1, 1},
  {0, 0, 0, 1, 0},
  {0, 0, 1, 0, 0}
};

//! 前ページ信号送出時ビットマップ
const uint8_t bmap_back[MICROBIT_LED_ROW][MICROBIT_LED_COL] =
{
  {0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0},
  {1, 1, 1, 1, 1},
  {0, 1, 0, 0, 0},
  {0, 0, 1, 0, 0}
};

void led_init()
{
  /**
    @fn
    micro:bitのLEDマトリックス初期化
  */
  for (int i = 0; i < max_cols; i++) {
    pinMode(cols[i], OUTPUT);
    digitalWrite(cols[i], HIGH);
  }
  for (int i = 0; i < max_rows; i++) {
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], LOW);
  }
}

void led_pset(const uint8_t x, const uint8_t y, const uint8_t mode) {
  POINT position = ledpos[y][x];
  digitalWrite(cols[position.x], !mode);
  digitalWrite(rows[position.y], mode);
}

void show_matrix(const uint8_t bmap[MICROBIT_LED_ROW][MICROBIT_LED_COL]) {
  int x, y;
  for (x = 0; x < MICROBIT_LED_COL; x++) {
    for (y = 0; y < MICROBIT_LED_ROW; y++) {
      POINT position = ledpos[y][x];
      if (bmap[y][x] == 1) {
        digitalWrite(cols[position.x], LOW );
        digitalWrite(rows[position.y], HIGH);
      } else {
        digitalWrite(cols[position.x], HIGH);
        digitalWrite(rows[position.y], LOW );
      }
    }
  }
}

void show_icon(BMAP_TYPE bmap_type) {
  switch (bmap_type)
  {
    case CONNECT:
      show_matrix(bmap_connect);
      break;
    case DISCONNECT:
      show_matrix(bmap_connect);
      break;
    case NEXT:
      show_matrix(bmap_next);
      break;
    case BACK:
      show_matrix(bmap_back);
      break;
    default:
      break;
  }
}
