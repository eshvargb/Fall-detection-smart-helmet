#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

long timer = 0;
const float FALL_THRESHOLD = 2.0;  // Threshold for detecting fall

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() {
  mpu6050.update();

  if (millis() - timer > 1000) {
    float accX = mpu6050.getAccX();
    float accY = mpu6050.getAccY();
    float accZ = mpu6050.getAccZ();

    // Calculate the total acceleration
    float totalAcc = sqrt(accX * accX + accY * accY + accZ * accZ);

    Serial.println("=======================================================");
    Serial.print("temp : "); Serial.println(mpu6050.getTemp());
    Serial.print("accX : "); Serial.print(accX);
    Serial.print("\taccY : "); Serial.print(accY);
    Serial.print("\taccZ : "); Serial.println(accZ);
    Serial.print("Total Acceleration: "); Serial.println(totalAcc);

    Serial.print("gyroX : "); Serial.print(mpu6050.getGyroX());
    Serial.print("\tgyroY : "); Serial.print(mpu6050.getGyroY());
    Serial.print("\tgyroZ : "); Serial.println(mpu6050.getGyroZ());

    Serial.print("accAngleX : "); Serial.print(mpu6050.getAccAngleX());
    Serial.print("\taccAngleY : "); Serial.println(mpu6050.getAccAngleY());

    Serial.print("gyroAngleX : "); Serial.print(mpu6050.getGyroAngleX());
    Serial.print("\tgyroAngleY : "); Serial.print(mpu6050.getGyroAngleY());
    Serial.print("\tgyroAngleZ : "); Serial.println(mpu6050.getGyroAngleZ());

    Serial.print("angleX : "); Serial.print(mpu6050.getAngleX());
    Serial.print("\tangleY : "); Serial.print(mpu6050.getAngleY());
    Serial.print("\tangleZ : "); Serial.println(mpu6050.getAngleZ());
    Serial.println("=======================================================\n");

    // Check for fall
    if (totalAcc < FALL_THRESHOLD) {
      Serial.println("Fall detected!");
    }

    timer = millis();
  }
}