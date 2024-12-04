#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "hello";
const char* password = "helloworld";
const char* serverIP = "192.168.243.220";  // Replace with ESP8266's IP
const int relayPin = 23;  // Adjust based on your setup

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi");
    Serial.print("ESP32 IP Address: ");
    Serial.println(WiFi.localIP());

    pinMode(relayPin, OUTPUT);
}

void loop() {
    if ((WiFi.status() == WL_CONNECTED)) {
        HTTPClient http;
        String url = String("http://") + serverIP + "/led";
        
        http.begin(url);
        int httpCode = http.GET();  // Send the request

        if (httpCode == 200) {  // HTTP OK
            String payload = http.getString();
            Serial.println("Received state: " + payload);
            
            // Control relay based on received state
            if (payload == "on") {
                digitalWrite(relayPin, HIGH);  // Turn LED on
            } else if (payload == "off") {
                digitalWrite(relayPin, LOW);  // Turn LED off
            }
        } else {
            Serial.println("Error on HTTP request");
        }
        http.end();
    } else {
        Serial.println("Wi-Fi disconnected");
    }

    delay(3000);  // Wait 3 seconds before next request
}


