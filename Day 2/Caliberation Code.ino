#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

float xMax = -100, xMin = 100;
float yMax = -100, yMin = 100;
float zMax = -100, zMin = 100;

void setup() {
  Serial.begin(115200);
  Wire.begin(21,22);

  Serial.println("Initializing MPU6050...");
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while(1);
  }

  Serial.println("Move the sensor slowly in all directions...");
}

void loop() {

  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);

  float Ax = ax / 16384.0;
  float Ay = ay / 16384.0;
  float Az = az / 16384.0;

  if(Ax > xMax) xMax = Ax;
  if(Ax < xMin) xMin = Ax;

  if(Ay > yMax) yMax = Ay;
  if(Ay < yMin) yMin = Ay;

  if(Az > zMax) zMax = Az;
  if(Az < zMin) zMin = Az;

  Serial.print("xMax: "); Serial.print(xMax);
  Serial.print("  xMin: "); Serial.print(xMin);

  Serial.print("  yMax: "); Serial.print(yMax);
  Serial.print("  yMin: "); Serial.print(yMin);

  Serial.print("  zMax: "); Serial.print(zMax);
  Serial.print("  zMin: "); Serial.println(zMin);

  delay(100);
}
