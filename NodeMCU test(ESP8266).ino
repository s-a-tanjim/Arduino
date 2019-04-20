#include<ESP8266WiFi.h>

#define led1 D1
#define led2 D2
#define led3 D3
#define led4 D4

const char* ssid="Name";
const char* password="PW Bola Jabe na";

WiFiClient client;
WiFiServer server(80);

String data="";

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid,password);

  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }
  Serial.println();
  Serial.println("Connected");

  server.begin();
  Serial.println("Server Connected!");
  Serial.print("Use this IP to connect:"); 
  Serial.print(WiFi.localIP());  
}

void loop() {

  client = server.available();
   if(!client)
   {
    return;
   }
   data = checkClient();

  if(data == "l1on")              //LED 1
    digitalWrite(led1,HIGH);
  else if(data == "l1off")
    digitalWrite(led1,LOW);

  if(data == "l2on")              //LED 2
    digitalWrite(led2,HIGH);
  else if(data == "l2off")
    digitalWrite(led2,LOW);

  if(data == "l3on")              //LED 3
    digitalWrite(led3,HIGH);
  else if(data == "l3off")
    digitalWrite(led3,LOW);

  if(data == "l4on")              //LED 4
    digitalWrite(led4,HIGH);
  else if(data == "l4off")
    digitalWrite(led4,LOW);
  

  client.println("HTTP/1.1 200 OK");
  client.println("Connect-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><title>My Home!</title></head>");
  client.println("<body>");
  client.println("<center>");
  client.println("<br><h1>LED Control System</h1><br><br><hr><hr><br><br><br");
  
  client.println("<a href=\"/l1on\"\"><button>LED 1 ON</button></a>");
  client.println("<a href=\"/l1off\"\"><button>LED 1 OFF</button></a>");

  client.println("<a href=\"/l2on\"\"><button>LED 2 ON</button></a>");
  client.println("<a href=\"/l2off\"\"><button>LED 2 OFF</button></a>");

  client.println("<a href=\"/l3on\"\"><button>LED 3 ON</button></a>");
  client.println("<a href=\"/l3off\"\"><button>LED 3 OFF</button></a>");

  client.println("<a href=\"/l4on\"\"><button>LED 4 ON</button></a>");
  client.println("<a href=\"/l4off\"\"><button>LED 4 OFF</button></a>");

  client.println("<br><br>");
  client.println("<hr>");
  client.println("<br><br>");
  client.println("<h3>Created by Tanjim</h3></center>");
  client.println("</body></html>");
  

}


String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}
