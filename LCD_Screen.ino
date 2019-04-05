#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
void setup() {
  lcd.begin(16,2);

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


}




