#include //required library 

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
}

void loop() {
Serial.println("Scanning WiFi...");

 //scan the networks present 

  for (int i = 0; i < networks; i++) {
   //print the available networks
  }

  delay(5000);
}
