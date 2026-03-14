#include <WiFi.h>
#include <Wire.h>
#include <MPU6050.h>
#include <WebSocketsServer.h>

/* ================= WIFI CONFIG ================= */

// "YOUR_WIFI_NAME"
// "YOUR_WIFI_PASSWORD"

/* ================= OBJECTS ================= */

// mpu 6050 object creation
// websocket object creation

/* ================= SENSOR VARIABLES ================= */

// Accelerometer
int16_t ax, ay, az;

// Gyroscope
int16_t gx, gy, gz;

// Orientation
float roll, pitch;

/* ================= SETUP ================= */

void setup() {

  Serial.begin(115200);

  /* ---------- WIFI ---------- */

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (// wifi status keyword() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("ESP32 IP Address: ");
  // print local ip address using keyword

  /* ---------- I2C ---------- */

  Wire.begin();

  /* ---------- MPU6050 ---------- */

  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected successfully");
  } else {
    Serial.println("MPU6050 connection FAILED");
  }

  /* ---------- WEBSOCKET ---------- */

  webSocket.begin();
  Serial.println("WebSocket Server Started");
}

/* ================= LOOP ================= */

void loop() {

  webSocket.loop();

  /* ---------- READ SENSOR ---------- */

  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);

  /* ---------- CONVERT TO FLOAT ---------- */

  float axf = ax;
  float ayf = ay;
  float azf = az;

  /* ---------- CALCULATE ORIENTATION ---------- */

  roll  = atan2(ayf, azf) * 180.0 / PI;
  pitch = atan2(-axf, sqrt(ayf * ayf + azf * azf)) * 180.0 / PI;

  /* ---------- DATA FORMAT ---------- */

  String data =
      String(ax) + "," +
      String(ay) + "," +
      String(az) + "," +
      String(gx) + "," +
      String(gy) + "," +
      String(gz) + "," +
      String(roll) + "," +
      String(pitch);

  /* ---------- SEND TO CLIENT ---------- */

 // data transfer

  /* ---------- DEBUG ---------- */

  Serial.print("AX:");
  Serial.print(ax);

  Serial.print(" AY:");
  Serial.print(ay);

  Serial.print(" AZ:");
  Serial.print(az);

  Serial.print(" GX:");
  Serial.print(gx);

  Serial.print(" GY:");
  Serial.print(gy);

  Serial.print(" GZ:");
  Serial.print(gz);

  Serial.print(" Roll:");
  Serial.print(roll);

  Serial.print(" Pitch:");
  Serial.println(pitch);

  delay(50);
}
