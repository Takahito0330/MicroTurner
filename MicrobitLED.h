/* 
 *  micro:bitのLEDマトリックス関連の定数定義
 *  https://github.com/ht-deko/microbit_Screenを参考にした
 */
#define MICROBIT_LED_ROW 5
#define MICROBIT_LED_COL 5

typedef struct TPoint {
  uint8_t x;
  uint8_t y;
} POINT;

const POINT ledpos[MICROBIT_LED_ROW][MICROBIT_LED_COL] =
{
  {{0, 0}, {3, 1}, {1, 0}, {4, 1}, {2, 0}},
  {{3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}},
  {{1, 1}, {8, 0}, {2, 1}, {8, 2}, {0, 1}},
  {{7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}},
  {{2, 2}, {6, 1}, {0, 2}, {5, 1}, {1, 2}}
};

//! 送出先デバイスのOS定義
enum BMAP_TYPE
{
  CONNECT,
  DISCONNECT,
  NEXT,
  BACK
};

void led_init(void);
void led_pset(const uint8_t, const uint8_t, const uint8_t);
void show_icon(BMAP_TYPE);
