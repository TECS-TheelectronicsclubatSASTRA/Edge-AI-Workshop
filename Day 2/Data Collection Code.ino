#include <Wire.h>
#include <MPU6050.h>
#include <WiFi.h>
#include <HTTPClient.h>

MPU6050 mpu;

/* =============================
    WIFI CONFIG
============================= */
const char* ssid = "ENTER YOUR SSID";
const char* password = "ENTER YOUR PASSWORD";
const char* serverName = "url";


/* =============================
   CALIBRATION VALUES
   paste your values!
============================= */
float xMax = ;
float xMin = ;
float yMax = ;
float yMin = ;
float zMax = ;
float zMin = ;

float xOffset, yOffset, zOffset;
float xScale, yScale, zScale;

/* =============================
   DATASET SETTINGS
============================= */
//define window size ,sample rate hertz, sampling interval

float Ax_arr[WINDOW_SIZE];
float Ay_arr[WINDOW_SIZE];
float Az_arr[WINDOW_SIZE];
float Gx_arr[WINDOW_SIZE];
float Gy_arr[WINDOW_SIZE];
float Gz_arr[WINDOW_SIZE];
//why isn't a "int" enough 


/* =============================
   SETUP
============================= */
void setup() {
  //set baud rate to 115200
  //Iniatialise the communication protocol

  Serial.println("Initializing MPU6050...");
  //intialise the mpu

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }

  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);

  // Compute calibration

  xOffset = (xMax + xMin) / 2.0;
  //calculate yOffset and zOffset

  xScale = 2.0 / (xMax - xMin);
  //calculate yScale and zScale

  Serial.println("Connecting to WiFi...");
  //initalise wifi with the right parameters 

  //check for connecticity

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

  //open a for loop with iteration set up to winow
  for  {

    while (millis() - lastSampleTime < SAMPLE_INTERVAL);
    lastSampleTime += SAMPLE_INTERVAL;

    //declare variables

    //get motion

    //calibrate 


    //store inside array
  }

  Serial.println("Recording complete.");
  sendBatchToGoogle(label);
}

/* =============================
   SEND TO GOOGLE
============================= */
void sendBatchToGoogle(String label) {

  //check for wifi connectiviity

  //object creation
  //begin
  //add header 

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
  //post it

  Serial.print("HTTP Response Code: ");
  //get the response
  //variable to get the code 
Serial.println(httpCode);


  //end posting
  Serial.println("Done.\n");
}

/* =============================
   LOOP
============================= */
void loop() {

  //check for serial monitor {

    //declare input as string 
    //align the right input

    
    //call the right function
  }
}
