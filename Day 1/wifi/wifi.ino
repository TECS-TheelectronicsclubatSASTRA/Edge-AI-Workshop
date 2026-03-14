#include <WiFi.h>


const char* ssid = "Enter your hotspot name";
const char* password = "tnter your password";


void setup() {
  Serial.begin(115200);
  Serial.println("Connecting to WiFi...");


  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }


  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
}
