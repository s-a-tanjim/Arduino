#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3
#define ir5 A4
#define ir6 A5


void setup() {
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  pinMode(ir3,INPUT);
  pinMode(ir4,INPUT);
  pinMode(ir5,INPUT);
  pinMode(ir6,INPUT);
  Serial.begin(9600);
}

void loop() {
  int a,b,c,d,e,f;
  a=analogRead(ir1);
  b=analogRead(ir2);
  c=analogRead(ir3);
  d=analogRead(ir4);
  e=analogRead(ir5);
  f=analogRead(ir6);

  
  Serial.print("IR1: ");
  Serial.print(a);
  Serial.print("  IR2: ");
  Serial.print(b);
  Serial.print("  IR3: ");
  Serial.print(c);
  Serial.print("  IR4: ");
  Serial.print(d);
  Serial.print("  IR5: ");
  Serial.print(e);
  Serial.print("  IR6: ");
  Serial.println(f);
  delay(500);
}
