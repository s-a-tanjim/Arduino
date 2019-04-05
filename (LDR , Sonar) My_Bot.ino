#include<LiquidCrystal.h>
#include<NewPing.h>

#define trig_left 53
#define echo_left 51
#define trig_front 52
#define echo_front 50
#define max_distance 200
#define left_pos 7
#define left_neg 6
#define right_pos 4
#define right_neg 5
#define right_pwm 3
#define left_pwm 8
int speeed_l= 100;
int speeed_r= 120;
int flag,distance_left,distance_front;
NewPing Sonar_left(trig_left,echo_left,max_distance);
NewPing Sonar_front(trig_front,echo_front,max_distance);
LiquidCrystal lcd(42,40,49,47,45,43);

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
  pinMode(left_pos,OUTPUT);
  pinMode(left_neg,OUTPUT);
  pinMode(right_pos,OUTPUT);
  pinMode(right_neg,OUTPUT);
  pinMode(right_pwm,OUTPUT);
  pinMode(left_pwm,OUTPUT);
 
}

void forward()
{
  digitalWrite(right_pos,HIGH);
  digitalWrite(right_neg,LOW);
  analogWrite(right_pwm,speeed_r);
  
  digitalWrite(left_pos,HIGH);
  digitalWrite(left_neg,LOW);
  analogWrite(left_pwm,speeed_l);
}

void backward()
{
  digitalWrite(right_pos,LOW);
  digitalWrite(right_neg,HIGH);
  analogWrite(right_pwm,speeed_r);
  
  digitalWrite(left_pos,LOW);
  digitalWrite(left_neg,HIGH);
  analogWrite(left_pwm,speeed_l);
}

void stopp()
{
  digitalWrite(right_pos,LOW);
  digitalWrite(right_neg,LOW);
  analogWrite(right_pwm,0);
  
  digitalWrite(left_pos,LOW);
  digitalWrite(left_neg,LOW);
  analogWrite(left_pwm,0);
}

void left()
{
  digitalWrite(right_pos,HIGH);
  digitalWrite(right_neg,LOW);
  analogWrite(right_pwm,speeed_r);
  digitalWrite(left_pos,LOW);
  digitalWrite(left_neg,HIGH);
  analogWrite(left_pwm,70);
}

void right()
{
  digitalWrite(right_pos,LOW);
  digitalWrite(right_neg,HIGH);
  analogWrite(right_pwm,70);
  
  digitalWrite(left_pos,HIGH);
  digitalWrite(left_neg,LOW);
  analogWrite(left_pwm,speeed_l);
}

void lcd_reading()
{
  lcd.setCursor(0,0);
  lcd.print("Left:");
  lcd.setCursor(6,0);
  lcd.print(distance_left);
  
  lcd.setCursor(0,1);
  lcd.print("Front:");
  lcd.setCursor(7,1);
  lcd.print(distance_front); 
}


void loop() 
{
  flag=0;
  distance_left=Sonar_left.ping_cm();
  distance_front=Sonar_front.ping_cm();
  lcd.clear();
  Serial.print("Left:  ");
  Serial.print(distance_left);
  Serial.print("    Front:  ");
  Serial.print(distance_front);
  Serial.println();
  lcd_reading();
  
  if ( distance_left <= 15)
  {
    lcd.setCursor(10,0);
    lcd.print("Right!");
    right();
    delay(500);
    flag=1;
  }
  else if (distance_front <= 12)
  {
    lcd.setCursor(10,0);
    lcd.print("Back!!");
    backward();
    delay(2000);
    lcd.clear();
    lcd_reading();
    lcd.setCursor(10,0);
    lcd.print("Left!!");
    left();
    delay(3000);
    flag=1;
  }
  if(flag==0)
  {
  forward();
  delay(300);
  }
  
  

}
