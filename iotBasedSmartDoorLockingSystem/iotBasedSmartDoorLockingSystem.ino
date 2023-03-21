#include <ESP8266WiFi.h>

const char* ssid ="akshaya";
const char* password ="16031599";

int LOCK =4;
WiFiServer Server(80);

void setup()
{
Serial.begin(9600);
delay(10);

pinMode(LOCK,OUTPUT);
digitalWrite(LOCK,LOW);

Serial.println();
Serial.println();
Serial.println("Connecting to");
Serial.println(ssid);

WiFi.begin(ssid,password);

while(WiFi.status() !=WL_CONNECTED)
{
delay(500);
Serial.println(".");
}

Serial.println("");
Serial.println("WIFi connected");

Server.begin();
Serial.println("server started");
Serial.println("");
Serial.println("***WiFi doorlock***");

Serial.println("Use thid url to connect");
Serial.println("http://");
Serial.println(WiFi.localIP());
Serial.println("/");

}


void loop()
{

WiFiClient client = Server.available();
if( !client)
{
return;
}


Serial.println("new client");
while(!client.available())
{
delay(1);
}

String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();


int value=LOW;
if(request.indexOf("/LOCK=ON")!=-1)
{
digitalWrite(LOCK, HIGH);
value= HIGH;
}

if(request.indexOf("/LOCK=OFF")!= -1)
{
digitalWrite(LOCK, LOW);
value= LOW;
}


client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("");
client.println("<!DOCTYPE HTML>");
client.println("<html>");

client.println("Door is now: ");

if(value== HIGH)
{
client.println("open");
}
else
{
client.println("closed");
}

client.println("<br><br>");
client.println("<a href=\"/LOCK=ON\"\"><button> <h1> Turn on </h1> </button> </a>");
client.println("<a href=\"/LOCK=OFF\"\"><button> <h1> Turn off </h1> </button> </a>");
client.println("</html>");


delay(1);

Serial.println("client disconnected");
Serial.println("");
}
