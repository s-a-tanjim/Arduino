void setup() {
Serial.begin(9600);
 pinMode(7, OUTPUT);
 }

void loop() {

 if(Serial.available()>0)
   {     
       //Serial.println("Serial Val: ..");
       //Serial.println(Serial.available());
      char data= Serial.read(); // reading the data received from the bluetooth module
      if(data=='F'){
        digitalWrite(7, HIGH);
      }
      else if(data=='B'){
        digitalWrite(7, LOW);
      }
      Serial.println(data);
   }
   delay(20);

}
