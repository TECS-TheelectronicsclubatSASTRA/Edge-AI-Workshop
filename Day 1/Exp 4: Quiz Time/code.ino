int ledPin = 2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  static float x=0;
  float y = 100*sin(x);
  Serial.println(y);
  if(y>0){
      digitalWrite(ledPin, HIGH);
    }
    else{
        digitalWrite(ledPin, LOW);
      }
  x+=0.1; 
  delay(20);
}
