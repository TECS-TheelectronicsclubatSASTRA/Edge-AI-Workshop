#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
}

void loop() {
Serial.println("Scanning WiFi...");

  int networks = WiFi.scanNetworks();

  for (int i = 0; i < networks; i++) {
    Serial.print(WiFi.SSID(i));
    Serial.print("  Signal:");
    Serial.println(WiFi.RSSI(i));
  }

  delay(5000);
}
