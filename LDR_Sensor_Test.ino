#define ldr A0
#define led 7
void setup() {
  pinMode(led,OUTPUT);
  pinMode(ldr,INPUT);
  Serial.begin(9600);
}

void loop() {
  int x=analogRead(ldr);
  Serial.println(x);
  if(x<=300)
  {
    digitalWrite (led,HIGH);
    Serial.println("Light is On!!");
  }
  else
  {
    digitalWrite(led,LOW);


  }
  delay(1000);


  
}
