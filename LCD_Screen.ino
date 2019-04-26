#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

void setup() 
{
  lcd.begin(16,2);    //16*2 grid
}

void loop() {
  int i,j,k;
  lcd.clear();
  
  for(i=1;i<=15;i=i+2)
  {
    lcd.setCursor(i,0);
    lcd.print(i);
    delay(300);
    lcd.clear();

    for(j=2;i<=15;j=j+2)
    {
      lcd.setCursor(j,1);
      lcd.print(j);
      delay(300);
      lcd.clear();
    }
  }
  lcd.print("Finished!!");
  delay(300);
}


/*

Functions:
  lcd.begin()
  lcd.print()
  lcd.setCursor()
  lcd.clear()
  
Pins:
  1 -> GND
  2 -> VCC (+5v)
  3 -> VO (Contrast)  (POT)  (**)
  4 -> RS (Register Select (Data memory))       (Arduino pin -> 2)
  5 -> R/W (Read / Write)  (GND)          
  6 -> E (Enable) (It makes 4 High)             (Arduino pin -> 3)
  7 -> D0   \
  8 -> D1   |
  9 -> D2   |
  10 -> D3  |## 8 Bit Data
  11 -> D4  |                                   (Arduino pin -> 4)|
  12 -> D5  |                                   (Arduino pin -> 5)\ using 4bit
  13 -> D6  |                                   (Arduino pin -> 6)/
  14 -> D7  /                                   (Arduino pin -> 7)|
  15 -> LED + [------ 1k(ohm)----- +5v] [it will connect with 1k ohm resistor. and other part of resistor will connect with +5v]
  16 -> LED - (GND)

Serial of LiquidCrystal lcd(2,3,4,5,6,7):   lcd(RS,E,D4,D5,D6,D7)

**: VO(3) will connect with POT. Other 2 part of POT will be VCC and GND. Decreasing resistance will increase brightness

*/
