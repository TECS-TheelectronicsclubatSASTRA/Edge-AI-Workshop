//declare the LED pin

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (Serial.available()) {  
   //read the input as char

   if (//condition for ON state) {
      digitalWrite(ledPin, HIGH);
    }

   else if (//condition for OFF state) {
      digitalWrite(ledPin, LOW);
    }
  }
}
