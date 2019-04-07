int pwm=255; //Forward Reverse Speed
int pwm1=160; //Left Right Speed
char data;


//Motors
#define rmp 26
#define rmm 27
#define rpf 5 //Right_motor_PWm_forward
#define rpr 6 //Right_motor_PWm_Reverse


#define lmp 38
#define lmm 39
#define lpf 8//Left_motor_PWm_forward
#define lpr 9 //Left_motor_PWm_reverse

int speeds=0;

void forward(); //go straight
void backward(); //go back

void tright(); //turn right
void tleft(); //turn left

void breaks(); //break



void setup() {
   Serial.begin(9600);

  //Motor pinMode

    //Right_Motor

  pinMode(rmp,OUTPUT);
  pinMode(rmm,OUTPUT);
  pinMode(rpf,OUTPUT);
  pinMode(rpr,OUTPUT);

    //Left_Motor
  pinMode(lmp,OUTPUT);
  pinMode(lmm,OUTPUT);
  pinMode(lpf,OUTPUT);
  pinMode(lpr,OUTPUT);

}

void loop() {

  if(Serial.available()>0)
  {
      data=Serial.read();
      Serial.println(data);
      Serial.print("Speed: ");
      Serial.println(speeds);
      if(data=='0' || data=='1' || data=='2' || data=='3' || data=='4' || data=='5' || data=='6' || data=='7' || data=='8' || data=='9')
      {
        speeds=(int)data-48;
        speeds*=27;
      }
      else if(data=='F') //Forward
      {
        forward();
      }
      else if(data=='B')  //Backward
      {
        backward();
        
      }
      else if(data=='R')    //Right  
      {
        tright();
      }
      else if(data=='L')    //Left  
      {
        tleft();
      }
      else if(data=='S')    //Normal input
      {
        breaks();
      }
      
      
  }
  delay(20);
}



void forward()
{ 
  
  digitalWrite(rmp,HIGH);
  digitalWrite(rmm,HIGH);
  analogWrite(rpf,speeds);
  analogWrite(rpr,0);

  
  digitalWrite(lmp,HIGH);
  digitalWrite(lmm,HIGH);
  analogWrite(lpf,speeds);
  analogWrite(lpr,0);
}

void backward()
{
  digitalWrite(rmp,HIGH);
  digitalWrite(rmm,HIGH);
  analogWrite(rpf,0);
  analogWrite(rpr,speeds);

  
  digitalWrite(lmp,HIGH);
  digitalWrite(lmm,HIGH);
  analogWrite(lpf,0);
  analogWrite(lpr,speeds);
}

void breaks()
{
  
  digitalWrite(rmp,LOW);
  digitalWrite(rmm,LOW);
  
  digitalWrite(lmp,LOW);
  digitalWrite(lmm,LOW);
}
void tright()
{
  
  digitalWrite(rmp,HIGH);
  digitalWrite(rmm,HIGH);
  analogWrite(rpf,0);
  analogWrite(rpr,speeds);

  
  digitalWrite(lmp,HIGH);
  digitalWrite(lmm,HIGH);
  analogWrite(lpf,speeds);
  analogWrite(lpr,0);
  
}

void tleft()
{
  
  
  digitalWrite(rmp,HIGH);
  digitalWrite(rmm,HIGH);
  analogWrite(rpf,speeds);
  analogWrite(rpr,0);

  
  digitalWrite(lmp,HIGH);
  digitalWrite(lmm,HIGH);
  analogWrite(lpf,0);
  analogWrite(lpr,speeds);
}
