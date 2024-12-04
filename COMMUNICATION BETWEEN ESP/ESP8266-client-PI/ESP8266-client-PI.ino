#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "hello";
const char* password = "helloworld";
const int ledPin = 5;  

ESP8266WebServer server(80);

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("... ");
    }
    Serial.println("\nConnected to Wi-Fi");
    Serial.print("ESP8266 IP Address: ");
    Serial.println(WiFi.localIP());

    pinMode(ledPin, OUTPUT);

    
    server.on("/control", []() {
        String command = server.arg("state");  // Get "state" query parameter
        
        if (command == "on") {
            digitalWrite(ledPin, HIGH);  
            Serial.println("LED IS OFF");
            server.send(200, "text/plain", "LED is ON");
        } else if (command == "off") {
            digitalWrite(ledPin, LOW); 
             Serial.println("LED IS OFF");
            server.send(200, "text/plain", "LED is OFF");
        } else {
            server.send(400, "text/plain", "Invalid command");
        }
    });

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}
