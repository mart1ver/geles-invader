/*
code du vaisseau


se connecte à la base et ordonne la pose et le décolage du vaisseau (la base fait décoller le vaisseau via un systeme de verin )

 */ 
 #include <Arduino.h>
 #include <Adafruit_NeoPixel.h>
 #include <Servo.h> 

 #include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <ESP8266HTTPClient.h>

 #define USE_SERIAL Serial
 #define LEDPIN            D4
 #define NUMPIXELS      2
 Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);
 unsigned long previousMillis = 0;        // will store last time LED was updated
 unsigned long previousMillis2 = 0;        // will store last time LED was updated
 const long interval = 20432;           // interval at which to blink (milliseconds)
 const long interval2 = 1200000;           // interval at which to blink (milliseconds)  normallement 1200000
 Servo myservo;  // create servo object to control a servo 
 Servo myservo1;  // create servo object to control a servo 
 Servo myservo2;  // create servo object to control a servo  

 void setup() {

 USE_SERIAL.begin(115200);
 WiFiManager wifiManager;
 wifiManager.setAPStaticIPConfig(IPAddress(192,168,4,2), IPAddress(192,168,4,2), IPAddress(255,255,255,0));
 wifiManager.autoConnect("AutoConnectAP");
 Serial.println("connected...yeey :)");
 
 
 if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 HTTPClient http;  //Declare an object of class HTTPClient
 http.begin("http://192.168.4.1/decole");  //Specify request destination
 int httpCode = http.GET();                                                                  //Send the request
 if (httpCode > 0) { //Check the returning code
 String payload = http.getString();   //Get the request response payload
 Serial.println(payload);                     //Print the response payload
 }
 http.end();   //Close connection
 }
 USE_SERIAL.println();
 USE_SERIAL.println();
 USE_SERIAL.println();
 for (uint8_t t = 4; t > 0; t--) {
 USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
 USE_SERIAL.flush();
 delay(1000);
 }
 pixels.begin(); // This initializes the NeoPixel library.
 myservo.attach(D3);  // attaches the servo on GIO2 to the servo object
 myservo1.attach(D5);  // attaches the servo on GIO2 to the servo object
 myservo2.attach(D6);  // attaches the servo on GIO2 to the servo object
 pinMode(D1, OUTPUT);
 pinMode(D2, OUTPUT);
 digitalWrite(D1, HIGH);   // on alume la ligne D1
 digitalWrite(D2, HIGH);   // turn the LED on (HIGH is the voltage level)
// manipulation du chargeur en position haute
 int pos;
 for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
 {                                  // in steps of 1 degree 
 myservo.write(pos);              // tell servo to go to position in variable 'pos' 
 delay(15);                       // waits 15ms for the servo to reach the position 
 } 
//initialisation des servos
 int pos1;
 for(pos1 = 0; pos1>=180; pos1+=1)     // goes from 180 degrees to 0 degrees 
 {                                
 myservo1.write(pos1);              // tell servo to go to position in variable 'pos' 
 delay(15);                       // waits 15ms for the servo to reach the position 
 }
 int pos2 = 180;
 for(pos2 = 0; pos2 <= 180; pos2 += 1) // goes from 0 degrees to 180 degrees 
 {                                  // in steps of 1 degree 
 myservo2.write(pos2);              // tell servo to go to position in variable 'pos' 
 delay(15);                       // waits 15ms for the servo to reach the position 
 } 
// alumage du VP
 for(pos1 = 0; pos1 <= 180; pos1 += 1) // goes from 0 degrees to 180 degrees 
 {                                  // in steps of 1 degree 
 myservo1.write(pos1);              // tell servo to go to position in variable 'pos' 
 delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos1 = 180; pos1>=0; pos1-=1)     // goes from 180 degrees to 0 degrees 
  {                                
  myservo1.write(pos1);              // tell servo to go to position in variable 'pos' 
  delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  delay(15000);
// lancement de la video
  for(pos2 = 180; pos2>=0; pos2-=1)     // goes from 180 degrees to 0 degrees 
  {                                
  myservo2.write(pos2);              // tell servo to go to position in variable 'pos' 
  delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos2 = 0; pos2 <= 180; pos2 += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
  myservo2.write(pos2);              // tell servo to go to position in variable 'pos' 
  delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  delay(3000);
  for(pos2 = 180; pos2>=0; pos2-=1)     // goes from 180 degrees to 0 degrees 
  {                                
  myservo2.write(pos2);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos2 = 0; pos2 <= 180; pos2 += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo2.write(pos2);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
  delay(3000); 
  for(pos2 = 180; pos2>=0; pos2-=1)     // goes from 180 degrees to 0 degrees 
  {                                
  myservo2.write(pos2);              // tell servo to go to position in variable 'pos' 
  delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos2 = 0; pos2 <= 180; pos2 += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
  myservo2.write(pos2);              // tell servo to go to position in variable 'pos' 
  delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  delay(3000);
   for(pos2 = 180; pos2>=0; pos2-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo2.write(pos2);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos2 = 0; pos2 <= 180; pos2 += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
  myservo2.write(pos2);              // tell servo to go to position in variable 'pos' 
  delay(15);                       // waits 15ms for the servo to reach the position 
  } 
}



void loop() {

 for(int i=0;i<2;i++){

    pixels.setPixelColor(i, pixels.Color(200,200,200)); 
    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(5000); // Delay for a period of time (in milliseconds).

  }
for(int i=0;i<1;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(27); // Delay for a period of time (in milliseconds).

  }
  for(int i=0;i<2;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(200,200,200)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(500); // Delay for a period of time (in milliseconds).

  }
for(int i=0;i<1;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(27); // Delay for a period of time (in milliseconds).

  }
  for(int i=0;i<2;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(200,200,200)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(30); // Delay for a period of time (in milliseconds).

  }
for(int i=0;i<1;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(35); // Delay for a period of time (in milliseconds).





  }
//random glitch du panneau D2
  unsigned long currentMillis = millis();
   unsigned long currentMillis2 = millis();
    if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // set the LED with the ledState of the variable:
    digitalWrite(D2, LOW);
    delay(random(120, 500));
    digitalWrite(D2, HIGH);
    delay(random(120, 500));
    digitalWrite(D2, LOW);
    delay(random(120, 500));
    digitalWrite(D2, HIGH);
    delay(random(120, 500));  
    digitalWrite(D2, LOW);
    delay(random(120, 500));
    digitalWrite(D2, HIGH);
    delay(random(120, 500));
  }
int pos = 0 ;

    if (currentMillis2 - previousMillis2 >= interval2) {
   // à la fin du film on pose le vaisseau*
  
 myservo.write(pos);              // tell servo to go to position in variable 'pos' 
 delay(1500);                       // waits 15ms for the servo to reach the position 
 

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 HTTPClient http;  //Declare an object of class HTTPClient
 http.begin("http://192.168.4.1/pose");  //Specify request destination
 int httpCode = http.GET();                                                                  //Send the request
 if (httpCode > 0) { //Check the returning code
 String payload = http.getString();   //Get the request response payload
 Serial.println(payload);                     //Print the response payload
 }
 http.end();   //Close connection
  delay(30000);    //Send a request every 30 seconds
 }

   
  }



int sensorValue = analogRead(A0);
 Serial.println(sensorValue);

 if (sensorValue > 200) {
  
  
   
   // à la fin du film on pose le vaisseau*
  
 myservo.write(pos);              // tell servo to go to position in variable 'pos' 
 delay(1500);                       // waits 15ms for the servo to reach the position 
 

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 HTTPClient http;  //Declare an object of class HTTPClient
 http.begin("http://192.168.4.1/pose");  //Specify request destination
 int httpCode = http.GET();                                                                  //Send the request
 if (httpCode > 0) { //Check the returning code
 String payload = http.getString();   //Get the request response payload
 Serial.println(payload);                     //Print the response payload
 }
 http.end();   //Close connection
  delay(30000);    //Send a request every 30 seconds
 }

   
  
  
  }



 
}
