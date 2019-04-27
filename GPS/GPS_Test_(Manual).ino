//$GPGLL, LAT , North/South , LONG, East/West , Time , V/A(A for OK, V for Warning) , N*64
//$GPGLL,,,,,,V,N*64
//$GPGLL,2348.80817,N,09023.48957,E,063329.00,A,A*60

//$GPGGA,063330.00,2348.80821,N,09023.48954,E,1,07,1.73,22.6,M,-49.5,M,,*4A
//$GPGGA, Time , Latitude , N/S , Longitude , E/W , 0/1/2 (0=Invalid, 1=GPS fix, 2=DGPS fix), Numb Of Satellite, HDOP , Altitude , Altitude Unit, ......

//Lat,long = remain space of 12 digit in lcd display
#include<LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);

String inputString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete

//For GPGLL
String SignalGLL = "$GPGLL";
char Latitude[15] , Longitude[15], Time[15],nORs[3],eORw[3];

//For GPGGA
String SignalGGA = "$GPGGA";
char LatitudeGGA[15] , LongitudeGGA[15], TimeGGA[15],nORsGGA[3],eORwGGA[3],numb_of_satellite[5],altitude_val[10],altitude_unit[5];


void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  inputString.reserve(200);
}

void loop() {
  
    if (stringComplete) {
      
        Serial.println(inputString);
        String BB = inputString.substring(0, 6);
        Serial.println(BB);
        /*
        //From GGL
        if (BB == SignalGLL) {
            //..................................String Modify.................

            int i,j;
            for(i=7,j=0 ; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++,j++)
            {
              Latitude[j]=inputString[i];
            }
            Latitude[j]='\0';
            i++;

            for(j=0 ; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++,j++)
            {
              nORs[j]=inputString[i];
            }
            nORs[j]='\0';
            i++;

            for(j=0 ; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++,j++)
            {
              Longitude[j]=inputString[i];
            }
            Longitude[j]='\0';
            i++;

            for(j=0 ; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++,j++)
            {
              eORw[j]=inputString[i];
            }
            eORw[j]='\0';
            i++;

            for(j=0 ; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++,j++)
            {
              Time[j]=inputString[i];
            }
            Time[j]='\0';
            i++;
            
            Serial.println("From GLL: ");
            Serial.print("Time :  ");
            if(Time[0]=='\0')
              Serial.println("NULL");
             else
              Serial.println(Time);
            Serial.print("Latitude :  ");
            if(Latitude[0]=='\0')
              Serial.println("NULL");
            else{
              Serial.print(Latitude);
              Serial.print("   ");
              Serial.println(nORs);
            }
            Serial.print("Longitude :  ");
            if(Longitude[0]=='\0')
              Serial.println("NULL");
             else{
              Serial.print(Longitude);
              Serial.print("   ");
              Serial.println(eORw);
             }
            
            lcd.clear();
            
            lcd.setCursor(0,0);
            lcd.print("Lt: ");
            lcd.setCursor(4,0);
            if(Latitude[0]=='\0')
              lcd.print("NULL");
            else
              lcd.print(Latitude);

            lcd.setCursor(0,1);
            lcd.print("Lg: ");
            lcd.setCursor(4,1);
            if(Longitude[0]=='\0')
              lcd.print("NULL");
            else
              lcd.print(Longitude);
            
            delay(3000);
            

        }
        */
        //From GGA Value:
        
        if(BB==SignalGGA)
        {
            int i,j;
            for(i=7,j=0 ; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++,j++)
            {
              TimeGGA[j]=inputString[i];
            }
            TimeGGA[j]='\0';
            i++;
            
            for(j=0 ; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++,j++)
            {
              LatitudeGGA[j]=inputString[i];
            }
            LatitudeGGA[j]='\0';
            i++;

            for(j=0 ; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++,j++)
            {
              nORsGGA[j]=inputString[i];
            }
            nORsGGA[j]='\0';
            i++;

            for(j=0 ; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++,j++)
            {
              LongitudeGGA[j]=inputString[i];
            }
            LongitudeGGA[j]='\0';
            i++;

            for(j=0 ; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++,j++)
            {
              eORwGGA[j]=inputString[i];
            }
            eORwGGA[j]='\0';
            i++;

            for(; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++);
            i++;
            
            for(j=0 ; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++,j++)
            {
              numb_of_satellite[j]=inputString[i];
            }
            numb_of_satellite[j]='\0';
            i++;
            
            
            for(; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++);
            i++;
            
            
            for(j=0 ; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++,j++)
            {
              altitude_val[j]=inputString[i];
            }
            altitude_val[j]='\0';
            i++;
            
            
            for(j=0 ; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++,j++)
            {
              altitude_unit[j]=inputString[i];
            }
            altitude_unit[j]='\0';
            i++;
            
            Serial.println("From GGA: ");
            Serial.print("Time :  ");
            if(TimeGGA[0]=='\0')
              Serial.println("NULL");
             else
              Serial.println(TimeGGA);
            Serial.print("Latitude :  ");
            if(LatitudeGGA[0]=='\0')
              Serial.println("NULL");
            else{
              Serial.print(LatitudeGGA);
              Serial.print("   ");
              Serial.println(nORsGGA);
            }
            Serial.print("Longitude :  ");
            if(LongitudeGGA[0]=='\0')
              Serial.println("NULL");
             else{
              Serial.print(LongitudeGGA);
              Serial.print("   ");
              Serial.println(eORwGGA);
             }
             
             Serial.print("Number of Satellites :  ");
             Serial.println(numb_of_satellite);
             
             Serial.print("Above mean sea level : ");
             Serial.print(altitude_val);
             Serial.print("   ");
             Serial.println(altitude_unit);
            
            lcd.clear();
            
            lcd.setCursor(0,0);
            lcd.print("Lt: ");
            lcd.setCursor(4,0);
            if(LatitudeGGA[0]=='\0')
              lcd.print("NULL");
            else
              lcd.print(LatitudeGGA);

            lcd.setCursor(0,1);
            lcd.print("Lg: ");
            lcd.setCursor(4,1);
            if(LongitudeGGA[0]=='\0')
              lcd.print("NULL");
            else
              lcd.print(LongitudeGGA);
            
            delay(3000);
            
          
        }
        
        else{
            lcd.setCursor(15,0);
            lcd.print("B");
        }
        stringComplete = false;
        inputString ="";
        //delay(2300);
    }
    else{
        lcd.setCursor(15,1);
            lcd.print("I");
    }
}


void serialEvent() {
    while (Serial.available()) {
      //Serial.println("Serial is available");
        // get the new byte:
        char inChar = (char) Serial.read();
        //Serial.println(inChar);
        // add it to the inputString:
        inputString += inChar;
        // if the incoming character is a newline, set a flag
        // so the main loop can do something about it:
        if (inChar == '\n') {
            stringComplete = true;
        }
    }
}
