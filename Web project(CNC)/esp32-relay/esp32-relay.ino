#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "hello";
const char* password = "helloworld";

WebServer server(80);
const int relay1Pin = 4; 
const int relay2Pin = 14; 

void handleControl() {
  String command = server.arg("plain");
  if (command == "RELAY1_ON") {
    digitalWrite(relay1Pin, LOW); 
    server.send(200, "text/plain", "Relay 1 is ON");
  } else if (command == "RELAY2_ON") {
    digitalWrite(relay2Pin, LOW); 
    server.send(200, "text/plain", "Relay 2 is ON");
  } else {
    server.send(400, "text/plain", "Invalid Command");
  }
}

void setup() {
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  digitalWrite(relay1Pin, HIGH); 
  digitalWrite(relay2Pin, HIGH);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.println(WiFi.localIP());

  server.on("/control", HTTP_POST, handleControl);
  server.begin();
}

void loop() {
  server.handleClient();
}
