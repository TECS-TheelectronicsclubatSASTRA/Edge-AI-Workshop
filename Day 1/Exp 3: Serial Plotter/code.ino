void setup() {
  Serial.begin(115200);
}

void loop() {
  static float x = 0;

  float y = 100 + sin(x); // generate wave

  Serial.println(y);

  x+= 0.1;  // Increment x
  delay(20);
}
