

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

int ledState = LOW;     

unsigned long previousMillis = 0;
const long interval = 1000;

/* Set these to your desired credentials. */
const char *ssid = "ESPap";
const char *password = "thereisnospoon";

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected to the base</h1>");
}

void setup() {
  pinMode(D2, OUTPUT);//sens de rotation du moteur
  pinMode(D3, OUTPUT);// marche moteur
  pinMode(D3, INPUT);//capteur plateau en position basse
  pinMode(D4, INPUT);//capteur plateau en position haute
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
  server.on("/pose", [](){
    server.send(200, "text/html", "OK! on pose le vaisseau!.");
   
  });


    server.on("/décole", [](){
    server.send(200, "text/html", "OK! on decole le vaisseau!.");
   
  });
}

void loop() {
  server.handleClient();
    unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
    if (ledState == LOW)
      ledState = HIGH;  // Note that this switches the LED *off*
    else
      ledState = LOW;   // Note that this switches the LED *on*
    digitalWrite(D2, ledState);
  }
}
