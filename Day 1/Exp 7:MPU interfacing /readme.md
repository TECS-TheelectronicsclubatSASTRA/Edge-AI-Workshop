# MPU6050 Sensor Reading with ESP32

This program reads **accelerometer and gyroscope data** from the MPU6050 sensor using I2C communication .

## Pin Connections

| MPU6050 | ESP32 |
|-------|------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |


## Output
The serial monitor displays:
Accel: ax ay az | Gyro: gx gy gz
