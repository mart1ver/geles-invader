
#include <Adafruit_NeoPixel.h>
#define PIXELSPIN          D7
#define NUMPIXELS      2
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXELSPIN, NEO_GRB + NEO_KHZ800);
ESP8266WebServer server(80);
void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  Serial.begin(9600);
  pinMode(D1, OUTPUT);// marche moteur
  pinMode(D0, OUTPUT);// sens de rotation du moteur
  digitalWrite(D1, HIGH);
  digitalWrite(D0, LOW);
  pinMode(D5, INPUT);//capteur plateau en position basse
  pinMode(D6, INPUT);//capteur plateau en position haute
  pinMode(A0, INPUT);//bouton de décolage forcé
  Serial.println();
  Serial.print("Setting soft-AP configuration ... ");
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP("atterrisseur") ? "Ready" : "Failed!");
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
  Serial.println();
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
  server.on("/decole", []() {
  decole();
  });
  server.on("/pose", []() {
  pose();
  });
  pixels.setPixelColor(0, pixels.Color(200, 0, 0)); // Moderately bright green color.
  pixels.show(); // This sends the updated pixel color to the hardware.
}



void loop() {
  server.handleClient();
  //delay(20);
  int sensorValue = analogRead(A0);
 Serial.println(sensorValue);


  if (sensorValue > 200) {
  
  
   
   // à la fin du film on pose le vaisseau*
  decole();
 }

   
  
  
  

}





void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected to the base my friend</h1>");
}
void decole() {
  server.send(200, "text/html", "OK! on decole le vaisseau!. <a href='../pose'> pose</a> ");
  digitalWrite(D1, LOW);
  digitalWrite(D0, HIGH);
  while (digitalRead(D6) == 0) {
  delay(20);
  }
  digitalWrite(D1, HIGH);
}
void pose() {
   server.send(200, "text/html", "OK! on pose le vaisseau!. <a href='../decole'> decole</a>");
   digitalWrite(D1, LOW);
   digitalWrite(D0, LOW);
   delay(20);
   while (digitalRead(D5) == 0) {
    delay(20);
   }
   digitalWrite(D1, HIGH);
}
