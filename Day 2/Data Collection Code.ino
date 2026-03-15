#include <Wire.h>
#include <MPU6050.h>
#include <WiFi.h>
#include <HTTPClient.h>

MPU6050 mpu;

/* =============================
    WIFI CONFIG
============================= */
const char* ssid = "SSID";
const char* password = "Password";
const char* serverName = "Your URL";
/* =============================
   CALIBRATION VALUES
============================= */
float xMax = 1.03;
float xMin = -0.96;
float yMax = 1.02;
float yMin = -1.00;
float zMax = 1.26;
float zMin = -0.79;

float xOffset, yOffset, zOffset;
float xScale, yScale, zScale;

/* =============================
   DATASET SETTINGS
============================= */
#define WINDOW_SIZE 200
#define SAMPLE_RATE_HZ 100
#define SAMPLE_INTERVAL 10  // ms

float Ax_arr[WINDOW_SIZE];
float Ay_arr[WINDOW_SIZE];
float Az_arr[WINDOW_SIZE];
float Gx_arr[WINDOW_SIZE];
float Gy_arr[WINDOW_SIZE];
float Gz_arr[WINDOW_SIZE];

/* =============================
   SETUP
============================= */
void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  Serial.println("Initializing MPU6050...");
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }

  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);

  // Compute calibration
  xOffset = (xMax + xMin) / 2.0;
  yOffset = (yMax + yMin) / 2.0;
  zOffset = (zMax + zMin) / 2.0;

  xScale = 2.0 / (xMax - xMin);
  yScale = 2.0 / (yMax - yMin);
  zScale = 2.0 / (zMax - zMin);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.println("Type Z, V, R, or I and press ENTER to record.");
}

/* =============================
   RECORD FUNCTION
============================= */
void recordGesture(String label) {

  Serial.println("Prepare...");
  delay(1000);

  Serial.println("Recording...");

  unsigned long lastSampleTime = millis();

  for (int i = 0; i < WINDOW_SIZE; i++) {

    while (millis() - lastSampleTime < SAMPLE_INTERVAL);
    lastSampleTime += SAMPLE_INTERVAL;

    int16_t ax_raw, ay_raw, az_raw;
    int16_t gx_raw, gy_raw, gz_raw;

    mpu.getMotion6(&ax_raw, &ay_raw, &az_raw,
                   &gx_raw, &gy_raw, &gz_raw);

    float Ax = ax_raw / 16384.0;
    float Ay = ay_raw / 16384.0;
    float Az = az_raw / 16384.0;

    Ax = xScale * (Ax - xOffset);
    Ay = yScale * (Ay - yOffset);
    Az = zScale * (Az - zOffset);

    float Gx = gx_raw / 131.0;
    float Gy = gy_raw / 131.0;
    float Gz = gz_raw / 131.0;

    Ax_arr[i] = Ax;
    Ay_arr[i] = Ay;
    Az_arr[i] = Az;
    Gx_arr[i] = Gx;
    Gy_arr[i] = Gy;
    Gz_arr[i] = Gz;
  }

  Serial.println("Recording complete.");
  sendBatchToGoogle(label);
}

/* =============================
   SEND TO GOOGLE
============================= */
void sendBatchToGoogle(String label) {

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    return;
  }

  HTTPClient http;
  http.begin(serverName);
  http.addHeader("Content-Type", "application/json");

  String json = "{";
  json += "\"label\":\"" + label + "\",";
  json += "\"data\":[";

  for (int i = 0; i < WINDOW_SIZE; i++) {

    json += "[";
    json += String(Ax_arr[i], 4) + ",";
    json += String(Ay_arr[i], 4) + ",";
    json += String(Az_arr[i], 4) + ",";
    json += String(Gx_arr[i], 4) + ",";
    json += String(Gy_arr[i], 4) + ",";
    json += String(Gz_arr[i], 4);
    json += "]";

    if (i < WINDOW_SIZE - 1) json += ",";
  }

  json += "]}";

  Serial.println("Sending data to Google Sheets...");
  int response = http.POST(json);

  Serial.print("HTTP Response Code: ");
  Serial.println(response);
  int httpCode = http.GET();
  Serial.println(httpCode);

  http.end();
  Serial.println("Done.\n");
}

/* =============================
   LOOP
============================= */
void loop() {

  if (Serial.available()) {

    String input = Serial.readStringUntil('\n');
    input.trim();

   
    if (input == "Z") recordGesture("zigzag");
    else if (input == "V") recordGesture("vertical");
    else if (input == "R") recordGesture("random");
    else if (input == "I") recordGesture("idle");
  }
}
