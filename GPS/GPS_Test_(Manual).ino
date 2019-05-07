//$GPGLL, LAT , North/South , LONG, East/West , Time , V/A(A for OK, V for Warning) , N*64
//$GPGLL,,,,,,V,N*64
//$GPGLL,2348.80817,N,09023.48957,E,063329.00,A,A*60

//$GPGGA,063330.00,2348.80821,N,09023.48954,E,1,07,1.73,22.6,M,-49.5,M,,*4A
//$GPGGA, Time , Latitude , N/S , Longitude , E/W , 0/1/2 (0=Invalid, 1=GPS fix, 2=DGPS fix), Numb Of Satellite, HDOP , Altitude , Altitude Unit, ......

//Lat,long = remain space of 12 digit in lcd display
#include<LiquidCrystal.h>

String inputString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete

//For GPGLL
String SignalGLL = "$GPGLL";
char Latitude[15] , Longitude[15], Time[15],nORs[3],eORw[3];

//For GPGGA
String SignalGGA = "$GPGGA";
char numb_of_satellite[5],altitude_val[10],altitude_unit[5];  //Latitude[15] , Longitude[15], Time[15],nORs[3],eORw[3],


LiquidCrystal lcd(2,3,4,5,6,7);

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  inputString.reserve(200);
}

void loop() {
  
    if (stringComplete) {
      
        //Serial.println(inputString);
        String BB = inputString.substring(0, 6);
        //Serial.println(BB);
        /*
        //From GGL
        if (BB == SignalGLL)
        {
            int i=7;
            i=dataPicker(i,Latitude);
            i=dataPicker(i,nORs);
            i=dataPicker(i,Longitude);
            i=dataPicker(i,eORw);
            i=dataPicker(i,Time);

            serialPrint("GLL");
            lcdPrint();
            delay(3000);
        }
        */
        //From GGA Value:
        if(BB==SignalGGA)
        {
            int i=7;
            i=dataPicker(i,Time);
            i=dataPicker(i,Latitude);
            i=dataPicker(i,nORs);
            i=dataPicker(i,Longitude);
            i=dataPicker(i,eORw);
            
            for(; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++);
            i++;
            
            i=dataPicker(i,numb_of_satellite);
           
            for(; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++);
            i++;
            
            i=dataPicker(i,altitude_val);
            i=dataPicker(i,altitude_unit);
            serialPrint("GGA");
            lcdPrint();
            delay(3000);
        }
        else
        {
            lcd.setCursor(15,0);
            lcd.print("B");
        }
        stringComplete = false;
        inputString ="";
        //delay(2300);
    }
    else
    {
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

void lcdPrint()
{
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
}

void serialPrint(String s)
{
  if(s=="GGA")  Serial.println("From GGA: ");
  else Serial.println("From GLL: ");
  //Time Printing
  Serial.print("Time :  ");
  if(Time[0]=='\0')
    Serial.println("NULL");
  else
    Serial.println(Time);
  //Latitude Printing
  Serial.print("Latitude :  ");
  if(Latitude[0]=='\0')
    Serial.println("NULL");
  else{
    Serial.print(Latitude);
    Serial.print("   ");
    Serial.println(nORs);
  }
  //Longitude Printing
  Serial.print("Longitude :  ");
  if(Longitude[0]=='\0')
    Serial.println("NULL");
  else{
    Serial.print(Longitude);
    Serial.print("   ");
    Serial.println(eORw);
  }

  if(s=="GGA")
  {
    Serial.print("Number of Satellites :  ");
    Serial.println(numb_of_satellite);
                
    Serial.print("Above mean sea level : ");
    Serial.print(altitude_val);
    Serial.print("   ");
    Serial.println(altitude_unit);
  }
}

int dataPicker(int i,char a[])
{
  int j;
  for(j=0 ; inputString[i]!=',' && inputString[i]!='\n' && inputString[i]!='\0'; i++,j++)
  {
      a[j]=inputString[i];
  }
  a[j]='\0';
  i++;
  return i;
}

long double charToInt(char s[])
{
    int i,Count=0;
    //Checking String
    if(s[0]=='\0')
    {
      return -1;
    }
    for(int k=0;s[k]!='\0';k++)
    {
        if(s[k]<48 || s[k]>57)
            Count++;
    }
    if(Count>1) return -1;
    //Checked String

    long double Numb=0;
    for(i=0;s[i]!='\0' && s[i]!='.';i++)
    {
        double temp=s[i]-48;
        Numb=Numb*10+temp;
    }
    if(s[i]=='.')
    {
        int x=10;
        for(i++;s[i]!='\0';i++)
        {
            double temp=(double)(s[i]-48)/(double)x;
            Numb += temp;
            x*=10;
        }
    }
    return Numb;
}
