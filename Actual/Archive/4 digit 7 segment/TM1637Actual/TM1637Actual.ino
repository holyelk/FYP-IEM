#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

int user_score = 0;
int com_score = 0;

void setup()
{
    uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
    uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
    display.setBrightness(4, true);
    display.clear();
}

void loop()
{

  display.showNumberDecEx(com_score, 0, false, 2, 2);
  display.showNumberDecEx(user_score, 0b01000000, false, 2, 0);
}
