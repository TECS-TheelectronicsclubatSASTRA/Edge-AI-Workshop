#include //required library

void setup() {
  Serial.begin(115200);
  delay(2000);

  WiFi.mode(WIFI_STA);
    // initialize WiFi stack

  Serial.print("ESP32 MAC Address: ");
 //get mac address
}

void loop() {
//is it required?
}
