int ledPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {

  if (Serial.available()) {      
    char data = Serial.read();

   if (data == '1') {
      digitalWrite(ledPin, HIGH);
    }

   else if (data == '0') {
      digitalWrite(ledPin, LOW);
    }
  }
}
