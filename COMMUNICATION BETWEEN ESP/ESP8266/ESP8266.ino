#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "hello";
const char* password = "helloworld";

ESP8266WebServer server(80);
String ledState = "off"; 

void toggleLEDState() {
    ledState = (ledState == "off") ? "on" : "off";
}

void setup() {
    Serial.begin(115200);
    Serial.println("Setup started");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi");
    Serial.print("ESP8266 IP Address: ");
    Serial.println(WiFi.localIP());


    server.on("/led", []() {
        server.send(200, "text/plain", ledState);
    });

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
    toggleLEDState(); 
    Serial.println("Signal Sent");
    delay(3000);
}
