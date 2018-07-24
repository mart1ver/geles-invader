  #include <ESP8266WiFi.h>
  #include <WiFiClient.h> 
  #include <ESP8266WebServer.h>
  /* Set these to your desired credentials. */
  const char *ssid = "BASE";
  const char *password = "vert";
  ESP8266WebServer server(80);
  void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected to the base my friend</h1>");
  }
  void setup() {
  pinMode(D2, OUTPUT);// marche moteur
  pinMode(D8, OUTPUT);// sens de rotation du moteur
  digitalWrite(D8, HIGH);   
  digitalWrite(D2, HIGH);  
  pinMode(D3, INPUT);//capteur plateau en position basse
  pinMode(D10, INPUT);//capteur plateau en position haute
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
  server.on("/decole", [](){
  server.send(200, "text/html", "OK! on decole le vaisseau!.");  
  digitalWrite(D8, LOW);   
  digitalWrite(D2, HIGH);
  while(digitalRead(D10) == 0){
  delay(20);
  }                 
  digitalWrite(D8, HIGH);   
  });
  server.on("/pose", [](){
  server.send(200, "text/html", "OK! on pose le vaisseau!."); 
  digitalWrite(D8, LOW);   
  digitalWrite(D2, LOW);
  while(digitalRead(D3) == 0){
  delay(20);
  }          
  digitalWrite(D8, HIGH);   
  });
  }
  void loop() {
  server.handleClient();
  }
