#include<NewPing.h>
#include<Servo.h>
#define F_trig 51
#define F_echo 53
#define B_trig 49
#define B_echo 47
#define L_trig 43
#define L_echo 45
#define R_trig 50
#define R_echo 52
#define MaxDistance 200

#define L_motorP 42
#define L_motorN 44
#define L_motorPWM 7
#define R_motorP 46
#define R_motorN 48
#define R_motorPWM 6

//#define ir1_pin A15
#define ir2_pin A14
//#define ir3_pin A13
#define ir4_pin A12
#define ir5_pin A11
//#define ir6_pin A10
#define ir7_pin A9
//#define ir8_pin A8

#define led 8
#define ldr A0

#define servo_pin 5

int F_dis , B_dis , R_dis , L_dis , flag , ldr_value , angle=0 , servo_flag=0;
int Rspeed = 100;
int Lspeed = 100;
int ir1 , ir2 , ir3 , ir4 , ir5 , ir6 , ir7 , ir8 , total_ir, ir_flag=0;   //IR value(From Right side)
NewPing F_sonar(F_trig,F_echo,MaxDistance);
NewPing B_sonar(B_trig,B_echo,MaxDistance);
NewPing L_sonar(L_trig,L_echo,MaxDistance);
NewPing R_sonar(R_trig,R_echo,MaxDistance);
Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(R_motorP ,OUTPUT);              //Motor
  pinMode(R_motorN ,OUTPUT);
  pinMode(L_motorP ,OUTPUT);
  pinMode(L_motorN ,OUTPUT);
  pinMode(R_motorPWM ,OUTPUT);
  pinMode(L_motorPWM ,OUTPUT);

  //pinMode(ir1_pin,INPUT);
  pinMode(ir2_pin,INPUT);
  //pinMode(ir3_pin,INPUT);
  pinMode(ir4_pin,INPUT);
  pinMode(ir5_pin,INPUT);
  //pinMode(ir6_pin,INPUT);
  pinMode(ir7_pin,INPUT);
  //pinMode(ir8_pin,INPUT);

  pinMode(led,OUTPUT);
  pinMode(ldr,INPUT);

  servo.attach(servo_pin);
}

void forward()
{
    digitalWrite(R_motorP ,HIGH);
    digitalWrite(R_motorN ,LOW);
    analogWrite(R_motorPWM , Rspeed);
    digitalWrite(L_motorP ,HIGH);
    digitalWrite(L_motorN ,LOW);
    analogWrite(L_motorPWM, Lspeed);
}
void backward()
{
    digitalWrite(R_motorP ,LOW);
    digitalWrite(R_motorN ,HIGH);
    analogWrite(R_motorPWM, Rspeed);
    digitalWrite(L_motorP ,LOW);
    digitalWrite(L_motorN ,HIGH);
    analogWrite(L_motorPWM, Lspeed);
}
void right()
{
    digitalWrite(R_motorP ,LOW);
    digitalWrite(R_motorN ,HIGH);
    analogWrite(R_motorPWM, Rspeed);
    digitalWrite(L_motorP ,HIGH);
    digitalWrite(L_motorN ,LOW);
    analogWrite(L_motorPWM, Lspeed);
}
void left()
{
    digitalWrite(R_motorP ,HIGH);
    digitalWrite(R_motorN ,LOW);
    analogWrite(R_motorPWM, Rspeed);
    digitalWrite(L_motorP ,LOW);
    digitalWrite(L_motorN ,HIGH);
    analogWrite(L_motorPWM, Lspeed);
}
void stopp()
{
    digitalWrite(R_motorP ,LOW);
    digitalWrite(R_motorN ,LOW);
    analogWrite(R_motorPWM, 0);
    digitalWrite(L_motorP ,LOW);
    digitalWrite(L_motorN ,LOW);
    analogWrite(L_motorPWM, 0);
}
void serialMonitor()
{
  Serial.print("Forward Dis: ");
  Serial.println(F_dis);
  Serial.print("Backward Dis: ");
  Serial.println(B_dis);
  Serial.print("Right Dis: ");
  Serial.println(R_dis);
  Serial.print("Left Dis: ");
  Serial.println(L_dis);
  Serial.print(ir1);
  Serial.print("      ");
  Serial.print(ir2);
  Serial.print("      ");
  Serial.print(ir3);
  Serial.print("      ");
  Serial.print(ir4);
  Serial.print("      ");
  Serial.print(ir5);
  Serial.print("      ");
  Serial.print(ir6);
  Serial.print("      ");
  Serial.print(ir7);
  Serial.print("      ");
  Serial.print(ir8);
  Serial.println("      ");
  Serial.println("......");
  
}
//Main........................................................................................................................
void loop() {
  flag=0;
  F_dis=F_sonar.ping_cm();
  B_dis=B_sonar.ping_cm();
  R_dis=R_sonar.ping_cm();
  L_dis=L_sonar.ping_cm();
  
  //ir1=analogRead(ir1_pin);
  ir2=analogRead(ir2_pin);
 // ir3=analogRead(ir3_pin);
  ir4=analogRead(ir4_pin);
  ir5=analogRead(ir5_pin);
  //ir6=analogRead(ir6_pin);
  ir7=analogRead(ir7_pin);
 // ir8=analogRead(ir8_pin);
 // total_ir=(ir1+ir2+ir3+ir4+ir5+ir6+ir7+ir8)/8;
  
  ldr_value=analogRead(ldr);

  serialMonitor();
  if(ldr_value<=300)                  //For LDR
  {
    digitalWrite(led,HIGH);
  }
  else
  {
    digitalWrite(led,LOW);
  }

  if(ir2>=1 && ir2<=300 &&  ir7>=1 && ir7<=300)               //Run in IR Mode
  {
    if(ir4>=300 && ir4<=520 &&  ir5>=300 && ir5<=520)
    {
      forward();
    }
    ir_flag=0;
  }
  else                                          //In Sonar Mode
  {
    if(ir_flag==0)
    {
      delay(3000);
      ir_flag=1;
    }
  if(20<=F_dis && F_dis<=40)
  {
    servo.write(0);
  }
  else
  {
    servo.write(110);
  }

  if(1<=F_dis && F_dis<=35)
  {
    flag=1;
    backward();
    delay(200);
    right();
    delay(100);
  }
  else if(1<=B_dis && B_dis<=25)
  {
    flag=1;
    forward();
    delay(200);
  }
  else if(1<=R_dis && R_dis<=25)
  {
    flag=1;
    left();
    delay(200);
  }
  else if(1<=L_dis && L_dis<=25)
  {
    flag=1;
    right();
    delay(200);
  }

  if(flag==0)
  {
    forward();
    delay(200);
  }

  }
  

}
