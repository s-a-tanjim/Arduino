//By Shafayet
//For left side error= -ve
//For right side error= +ve
// 11111 000000 -1 -------


int sen_ana[10];               //storing sensor's analog value
int sen_dig[10];               //storing sensor's digital value
int ir=500;                   //comparative value for black surface
int sen_read[10]={A0,A1,A2,A3,A4,A5,A6,A7,A8,A9}; //analog pin
int pos;
int set_point=50;              //balance position of the bot
int error=0;                   //error position of the bot
int last_error=0;
int integral=0;
int derivative=0;

float kp=.01;
float ki=0;
float kd=60;

int correction=0;

//Motor Pin

int base_speeds=100;
int speeds;

//Motor Pin
#define rmp 22 //Right_Motor_Plus
#define rmm 23 //Might_Motor_Minus
#define rpw 6 //Might_motor_PWm

#define lmp 26 //Left_Motor_Plus
#define lmm 27 //Left_Motor_Minus
#define lpw 7 //Left_motor_PWm

//Functions

void right_motor_frw();
void right_motor_rev();
void right_motor_stop();

void left_motor_frw();
void left_motor_rev();
void left_motor_stop();

void forward();  //go straight
void backward(); //go back
void tleft();   //turn left
void tright();   //turn right

void pid();     //pid


void setup() {
  Serial.begin(9600);

  //Motor pinMode
  pinMode(rmp,OUTPUT);
  pinMode(rmm,OUTPUT);
  pinMode(rpw,OUTPUT);

  pinMode(lmp,OUTPUT);
  pinMode(lmm,OUTPUT);
  pinMode(lpw,OUTPUT);

}

void loop() {

  pid();

}

void pid()
{
  int i,j=10,sen_sum=0,sen_act=0;

  for(i=0;i<10;i++) //converting sensor's value from analog to digital
  { 
    sen_ana[i]=analogRead(sen_read[i]);
    Serial.print(sen_ana[i]);
    Serial.print(" ");
  }
  
  for(i=0;i<10;i++) //converting sensor's value from analog to digital
  { 
    sen_ana[i]=analogRead(sen_read[i]);
    if(sen_ana[i]>500)
    {
      sen_dig[i]=0;
    }
    else
    {
      sen_dig[i]=1;
    }
    Serial.print(sen_dig[i]);
    Serial.print(" ");
    sen_sum+=sen_dig[i]*j; //sensor sum for active sensors
    sen_act+=sen_dig[i]; //number of active sensors
    j+=10;
  } //analog to digital has been converted
  
  pos=sen_sum/sen_act; //position of the bot

  Serial.print("pos ");
  Serial.print(pos);
  Serial.print(" ");
  error=pos-set_point;
  if(error==-51)
  {
    error=0;
  }
  Serial.print("error ");
  Serial.print(error);
  Serial.print(" ");
  
  integral+=error;
  derivative=error-last_error;
  last_error=error;

  correction=kp*error+ki*integral+kd*derivative;
 
  if(correction>255)
  {
    correction=255;
  }
  if(correction<-255)
  {
    correction=-255;
  }
  
  Serial.print("correction ");
  Serial.print(correction);
  if(pos==-1)
  {
    speeds=0;
    breaks();
  }
  else if(error<0)
  {
    speeds=base_speeds-correction;
    Serial.print(" speed ");
    speeds=base_speeds; //Rem
    Serial.print(speeds);
    left_motor_frw();
    speeds=base_speeds;
    Serial.print(" speed ");
    Serial.print(speeds);
    right_motor_frw();
    
  }

  else if(error>0)
  {
    speeds=base_speeds;
    Serial.print(" speed ");
    Serial.print(speeds);
    left_motor_frw();
    speeds=base_speeds+correction;
    Serial.print(" speed ");
    Serial.print(speeds);
    right_motor_frw();
    
  }
  else if(error==0)
  {
    speeds=base_speeds;
    Serial.print(" speed ");
    Serial.print(speeds);
    forward();
  }
  else breaks;
  
  Serial.println("");
}

//#######################################


void right_motor_frw()
{
  digitalWrite(rmp,HIGH);
  digitalWrite(rmm,LOW);
  analogWrite(rpw,speeds);
}

void right_motor_rev()
{
  digitalWrite(rmp,LOW);
  digitalWrite(rmm,HIGH);
  analogWrite(rpw,speeds);
}

void right_motor_stop()
{
  digitalWrite(rmp,LOW);
  digitalWrite(rmm,LOW);
}

void left_motor_frw()
{
  digitalWrite(lmp,HIGH);
  digitalWrite(lmm,LOW);
  analogWrite(lpw,speeds);
}

void left_motor_rev()
{
  digitalWrite(lmp,LOW);
  digitalWrite(lmm,HIGH);
  analogWrite(lpw,speeds);
}

void left_motor_stop()
{
  digitalWrite(lmp,LOW);
  digitalWrite(lmm,LOW);
}

void forward() //go straight
{
  right_motor_frw();
  left_motor_frw();
}

void backward() //go back
{
  right_motor_rev();
  left_motor_rev();
}

void tright() //turn right
{
  right_motor_stop();
  left_motor_frw();
}

void tleft() //turn left
{
  right_motor_frw();
  left_motor_stop();
}

void breaks() //break
{
  right_motor_stop();
  left_motor_stop();
}
