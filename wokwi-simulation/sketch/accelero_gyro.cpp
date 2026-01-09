#include <Arduino.h>
#include "accelero_gyro.h"

static const uint8_t MPU_ADDR = 0x68;

static const uint8_t PWR_MGMT_1 = 0x6B;
static const uint8_t ACCEL_XOUT_H = 0x3B;
static const uint8_t GYRO_XOUT_H  = 0x43;

void setupAccelGyro() {
    Wire.begin(21, 22);

    Wire.beginTransmission(MPU_ADDR);
    Wire.write(PWR_MGMT_1);
    Wire.write(0);
    Wire.endTransmission();
}

static int16_t readWord(uint8_t reg) {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(reg);
    Wire.endTransmission(false);

    Wire.requestFrom(MPU_ADDR, 2);
    return (Wire.read() << 8) | Wire.read();
}

void updateAccelGyro() {
    float ax, ay, az, gx, gy, gz;

    int16_t rawAX = readWord(ACCEL_XOUT_H);
    int16_t rawAY = readWord(ACCEL_XOUT_H + 2);
    int16_t rawAZ = readWord(ACCEL_XOUT_H + 4);

    int16_t rawGX = readWord(GYRO_XOUT_H);
    int16_t rawGY = readWord(GYRO_XOUT_H + 2);
    int16_t rawGZ = readWord(GYRO_XOUT_H + 4);

    ax = rawAX / 16384.0;
    ay = rawAY / 16384.0;
    az = rawAZ / 16384.0;

    gx = rawGX / 131.0;
    gy = rawGY / 131.0;
    gz = rawGZ / 131.0;

    Serial.print("Accel (g): ");
    Serial.print(ax); Serial.print(", ");
    Serial.print(ay); Serial.print(", ");
    Serial.println(az);

    Serial.print("Gyro (deg/s): ");
    Serial.print(gx); Serial.print(", ");
    Serial.print(gy); Serial.print(", ");
    Serial.println(gz);
}
