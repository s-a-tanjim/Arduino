#include<Servo.h>
Servo servo_test;        //initialize a servo object for the connected servo  
                
int angle = 0;    
 
void setup() 
{ 
  servo_test.attach(6);      // attach the signal pin of servo to pin9 of arduino
} 
  
void loop() 
{ 

servo_test.write(0);
delay(3000);

servo_test.write(120);
delay(3000);

servo_test.write(20);
delay(3000);
servo_test.write(-20);
delay(3000);

}
