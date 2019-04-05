#include<LiquidCrystal.h>
#include<NewPing.h>
#define trig 6
#define echo 7
#define pwm_m1 2 //left motor
#define pwm_m2 3 //right motor
#define max_distance 200
LiquidCrystal lcd(8,9,10,11,12,13);
NewPing sonar(trig,echo,max_distance);
int speeds = 80;
void setup() {
  pinMode(36,OUTPUT); //left motor +
  pinMode(38,OUTPUT); //left motor -
  pinMode(40,OUTPUT); //right motor +
  pinMode(42,OUTPUT); //right motor -
  pinMode(2,OUTPUT); //left motor
  pinMode(3,OUTPUT); //right motor
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();

}
void display_format1()
{
  lcd.setCursor(0,0);
  lcd.print("Distance:");
  lcd.setCursor(13,0);
  lcd.print("cm");
}
void motor_forward(){
  digitalWrite(36,HIGH);
  digitalWrite(38,LOW);
  digitalWrite(40,HIGH);
  digitalWrite(42,LOW);
  analogWrite(pwm_m1,speeds);
  analogWrite(pwm_m2,speeds);
}
void motor_backward(){
  digitalWrite(36,LOW);
  digitalWrite(38,HIGH);
  digitalWrite(40,LOW);
  digitalWrite(42,HIGH);
  analogWrite(pwm_m1,speeds);
  analogWrite(pwm_m2,speeds);
}
void motor_left(){
  digitalWrite(36,HIGH);
  digitalWrite(38,LOW);
  digitalWrite(40,HIGH);
  digitalWrite(42,LOW);
  analogWrite(pwm_m1,10);
  analogWrite(pwm_m2,speeds);
}

void motor_right(){
  
  digitalWrite(36,HIGH);
  digitalWrite(38,LOW);
  digitalWrite(40,HIGH);
  digitalWrite(42,LOW);
  analogWrite(pwm_m1,speeds);
  analogWrite(pwm_m2,10);
}
void stopp()
{
  digitalWrite(36,LOW);
  digitalWrite(38,LOW);
  digitalWrite(40,LOW);
  digitalWrite(42,LOW);
}


void loop() {
  lcd.clear();
  int distance=sonar.ping_cm();
  motor_forward();
  Serial.println(distance);
  
  display_format1();
  lcd.setCursor(10,0);
  lcd.print(distance);
  
  if(0<distance<=20)
  {
    lcd.setCursor(0,1);
    lcd.print("Stop! Turn left");
    digitalWrite(5,HIGH);
    digitalWrite(4,LOW);
    stopp();
    delay(500);
    motor_backward();
    delay(2000);
    motor_left();
    delay(3000);
    stopp();
  }
  if (distance>20)
  {
    lcd.setCursor(0,1);
    lcd.print("Gooooo!!");
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
  }

  delay(500);

}
