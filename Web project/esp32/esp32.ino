#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Charan";
const char* password = "1212121212";

LiquidCrystal_I2C lcd(0x27, 16, 2);
WebServer server(80);

void handleDisplayMessage() {
  String message = server.arg("plain");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
  Serial.print(message);
  server.send(200, "text/plain", "Message displayed: " + message);
}

void setup() {
  lcd.begin(16,2);
  lcd.backlight();

    Serial.begin(115200);

  lcd.setCursor(0, 0);
  lcd.print("Connecting...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
 
  lcd.clear();
  lcd.print("Connected");

  server.on("/display-message", HTTP_POST, handleDisplayMessage);
  server.begin();
}

void loop() {
  server.handleClient();
}


