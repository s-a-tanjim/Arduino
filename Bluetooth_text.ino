void setup() {
Serial.begin(9600);
 pinMode(7, OUTPUT); // put your setup code here, to run once:
 }

void loop() {
  // put your main code here, to run repeatedly:

 if(Serial.available()>0)
   {     
       //Serial.println("Serial Val: ..");
       //Serial.println(Serial.available());
      char data= Serial.read(); // reading the data received from the bluetooth module
      if(data=='F'){
        digitalWrite(7, HIGH);
      }// when a is pressed on the app on your smart phone
      else if(data=='B'){
        digitalWrite(7, LOW); // when d is pressed on the app on your smart phone
      }
      Serial.println(data);
   }
   delay(20);

}
