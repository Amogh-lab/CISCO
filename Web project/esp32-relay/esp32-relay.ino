#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "hello";
const char* password = "helloworld";

WebServer server(80);
const int relayPins[] = {4, 14, 12, 13}; // Pins for relays 1, 2, 3, 4

void handleControl() {
  String command = server.arg("plain");
  if (command == "RELAY1_ON") {
    digitalWrite(relayPins[0], LOW);  // Turn Relay 1 ON
    server.send(200, "text/plain", "Relay 1 is ON");
  } else if (command == "RELAY1_OFF") {
    digitalWrite(relayPins[0], HIGH);  // Turn Relay 1 OFF
    server.send(200, "text/plain", "Relay 1 is OFF");
  } else if (command == "RELAY2_ON") {
    digitalWrite(relayPins[1], LOW);  // Turn Relay 2 ON
    server.send(200, "text/plain", "Relay 2 is ON");
  } else if (command == "RELAY2_OFF") {
    digitalWrite(relayPins[1], HIGH);  // Turn Relay 2 OFF
    server.send(200, "text/plain", "Relay 2 is OFF");
  } else if (command == "RELAY3_ON") {
    digitalWrite(relayPins[2], LOW);  // Turn Relay 3 ON
    server.send(200, "text/plain", "Relay 3 is ON");
  } else if (command == "RELAY3_OFF") {
    digitalWrite(relayPins[2], HIGH);  // Turn Relay 3 OFF
    server.send(200, "text/plain", "Relay 3 is OFF");
  } else if (command == "RELAY4_ON") {
    digitalWrite(relayPins[3], LOW);  // Turn Relay 4 ON
    server.send(200, "text/plain", "Relay 4 is ON");
  } else if (command == "RELAY4_OFF") {
    digitalWrite(relayPins[3], HIGH);  // Turn Relay 4 OFF
    server.send(200, "text/plain", "Relay 4 is OFF");
  } else {
    server.send(400, "text/plain", "Invalid Command");
  }
}

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH); // Start relays in OFF state (HIGH)
  }

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
