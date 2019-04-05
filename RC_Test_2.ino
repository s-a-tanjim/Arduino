//Motors
#define frmp 30 //Front_Right_Motor_Plus
#define frmm 31 //Front_Right_Motor_Minus
#define frpw 4 //Front_Right_motor_PWm

#define brmp 34 //Back_Right_Motor_Plus
#define brmm 35 //Back_Right_Motor_Minus
#define brpw 5//Back_Right_motor_PWm

#define flmp 22 //Front_Left_Motor_Plus
#define flmm 23 //Front_Left_Motor_Minus
#define flpw 3 //Front_Left_motor_PWm

#define blmp 26 //Back_Left_Motor_Plus
#define blmm 27 //Back_Left_Motor_Minus
#define blpw 2 //Back_Left_motor_PWm

//Channels

#define fb 7 //ch-2_Forward_Backward
#define ro 10 //ch-3 Rotate
#define lr 9 //ch-4 Left-Right
#define of 8 //ch-5 Max_speed

float speeds;

void right_motor_frw()
{
  digitalWrite(frmp,HIGH);
  digitalWrite(frmm,LOW);
  analogWrite(frpw,speeds);

  digitalWrite(brmp,HIGH);
  digitalWrite(brmm,LOW);
  analogWrite(brpw,speeds);
}

void right_motor_rev()
{
  digitalWrite(frmp,LOW);
  digitalWrite(frmm,HIGH);
  analogWrite(frpw,speeds);

  digitalWrite(brmp,LOW);
  digitalWrite(brmm,HIGH);
  analogWrite(brpw,speeds);
}

void right_motor_stop()
{
  digitalWrite(frmp,LOW);
  digitalWrite(frmm,LOW);

  digitalWrite(brmp,LOW);
  digitalWrite(brmm,LOW);
}

void left_motor_frw()
{
  digitalWrite(flmp,HIGH);
  digitalWrite(flmm,LOW);
  analogWrite(flpw,speeds);

  digitalWrite(blmp,HIGH);
  digitalWrite(blmm,LOW);
  analogWrite(blpw,speeds);
}

void left_motor_rev()
{
  digitalWrite(flmp,LOW);
  digitalWrite(flmm,HIGH);
  analogWrite(flpw,speeds);

  digitalWrite(blmp,LOW);
  digitalWrite(blmm,HIGH);
  analogWrite(blpw,speeds);
}

void left_motor_stop()
{
  digitalWrite(flmp,LOW);
  digitalWrite(flmm,LOW);

  digitalWrite(blmp,LOW);
  digitalWrite(blmm,LOW);
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
  right_motor_rev();
  left_motor_frw();
}

void tleft() //turn left
{
  right_motor_frw();
  left_motor_rev();
}

void breaks() //break
{
  right_motor_stop();
  left_motor_stop();
}


void setup() {
  Serial.begin(9600);

  //Motor pinMode
  pinMode(frmp,OUTPUT);
  pinMode(frmm,OUTPUT);
  pinMode(frpw,OUTPUT);

  pinMode(brmp,OUTPUT);
  pinMode(brmm,OUTPUT);
  pinMode(brpw,OUTPUT);

  pinMode(flmp,OUTPUT);
  pinMode(flmm,OUTPUT);
  pinMode(flpw,OUTPUT);

  pinMode(blmp,OUTPUT);
  pinMode(blmm,OUTPUT);
  pinMode(blpw,OUTPUT);

  //Channel-Mode
  pinMode(fb,INPUT);
  pinMode(lr,INPUT);
  pinMode(of,INPUT);
  pinMode(ro,INPUT);
}

void loop() {
  
  int fbx=pulseIn(fb,HIGH); //Forward_Backward Channel
  Serial.print("FB ");
  Serial.print(fbx);
  Serial.print(" ");

  int lrx=pulseIn(lr,HIGH); //Left_Right Channel
  Serial.print("LR ");
  Serial.print(lrx);
  Serial.print(" ");

  int ofx=pulseIn(of,HIGH); //On-Off Channel
  Serial.print("OF ");
  Serial.print(ofx);
  Serial.print(" ");

  int rox=pulseIn(ro,HIGH); //Rotation
  Serial.print("RO ");
  Serial.print(rox);
  Serial.print(" Speeds ");
  //Serial.println("");


  if(ofx<1200) //Switch
    {
     breaks();
    } 
  else
  { 
    //Forward Move
    if(fbx>1510)
  {
    int fby=constrain(fbx,1510,1800);
    speeds=map(fby,1510,1800,30,255);
    Serial.print(speeds);
    forward();
  } 
  
    //Backward Move
    
    if(fbx<1470)
    {
    int fby=constrain(fbx,1230,1470);
    speeds=map(fby,1470,1230,0,255);
    Serial.print(speeds);
    backward();
    }
    
    //Right Move
    if(lrx>1495)
    {
    int lry=constrain(lrx,1495,1800);
    speeds=map(lry,1495,1800,0,255);
    Serial.print(speeds);
    tright();
    }
    
      
      //Left Move
      if(lrx<1425)
    {
    int lry=constrain(lrx,1104,1475);
    speeds=map(lry,1425,1104,0,255);
    Serial.print(speeds);
    tleft();
     }
     }
  
 Serial.println("");
}




