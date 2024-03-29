
#include <ESP8266WiFi.h>

#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "Old Guys";
const char *password = "password";

int led1 = 13;
int led2 = 12;
int led3 = 14;
int bzz = 4;

ESP8266WebServer server(80);

void actLED();
void piscaLED(int);
void handleLED(){};
void handleRoot()
{

    server.send(200, "text/html", "<p><html> <head> <title>ESP8266 LED Control</title> </head> <body> <center><font size='40'> <a href='/?led=1'>Led 1 </a><br> <a href='/?led=2'> Led 2 </a><br> <a href='/?led=3'> Led 3 </a><br></font> </center> </body> </html></p>");
    actLED();
}

void setup()
{

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(bzz, OUTPUT);

    delay(1000);

    Serial.begin(9600);
    Serial.println();
    Serial.print("Configuring access point...");
    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP server started");
}

void loop()
{
    server.handleClient();
}

void piscaLED(int led)
{
    int i;

    for (i = 0; i < 20; i++)
    {
        delay(500);
        if (!digitalRead(led))
        {
            Serial.println(digitalRead(led));
            digitalWrite(led, HIGH);
            digitalWrite(bzz, HIGH);
        }
        else
        {
            Serial.println(digitalRead(led));
            digitalWrite(led, LOW);
            digitalWrite(bzz, LOW);
        }
    }
}

void actLED()
{

    String state = server.arg("led");
    if (state == "1")
    {
        piscaLED(led1);
    }
    if (state == "2")
    {
        piscaLED(led2);
    }
    if (state == "3")
    {
        piscaLED(led3);
    }
}