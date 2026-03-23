#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // RS, E, D4, D5, D6, D7

// special characters
byte rainCloudChar[8] = {
	0b01110,
	0b11111,
	0b11111,
	0b11111,
	0b10101,
	0b01010,
	0b10101,
	0b01010
};

void setup()
{
  lcd.begin(16, 2); //configures lcd as 16-column, 2 row display
  lcd.setCursor(0, 0);
  lcd.print("Current temp: ");
  
  lcd.createChar(0, rainCloudChar); // create a new custom character

  lcd.setCursor(13, 0); // move cursor to (2, 0)
  lcd.write((byte)0);  // print the custom char at (2, 0)
}

void loop()
{
}
