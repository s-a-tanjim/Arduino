#define trig 9
#define echo 10
//#define maxx 200

//NewPing Sonar(trig,echo,maxx);

void setup() {
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

void loop() {
  float distance,duration;
  //distance = Sonar.ping_cm();
  digitalWrite(trig , HIGH);
  delayMicroseconds(2);
  digitalWrite(trig,LOW);

  digitalWrite(trig , HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  
  duration= pulseIn(echo,HIGH);

  distance= duration*0.03506/2;

  Serial.print("Distance:  ");
  Serial.print(distance);
  Serial.println("");
  delay(1000);





}
