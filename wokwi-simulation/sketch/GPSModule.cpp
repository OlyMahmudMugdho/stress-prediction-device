#include "GPSModule.h"

static double lastAltitude = 0.0;
static double lastSpeed = 0.0;
static bool hasAltitude = false;
static bool hasSpeed = false;


// Forward declarations
static void printLocation();
static void printSpeed();
static void printDateTime();

TinyGPSPlus gps;

void initGPS() {
  // Serial already started in sketch
  Serial.println(F("NEO6M GPS Module Initialized on RX/TX"));
}

bool readGPSData() {
  bool updated = false;

  while (Serial.available() > 0) {
    if (gps.encode(Serial.read())) {
      printLocation();
      printSpeed();
      printDateTime();
      Serial.println();
      updated = true;
    }
  }

  return updated;
}

static void printLocation() {
  Serial.print(F("Location:\t("));

  if (gps.location.isValid()) {
    Serial.print(F("Latitude: "));
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(", Longitude: "));
    Serial.print(gps.location.lng(), 6);
    Serial.print(F(", Altitude: "));

    if (gps.altitude.isValid()) {
      lastAltitude = gps.altitude.meters();
      hasAltitude = true;
      Serial.print(lastAltitude);
    } else if (hasAltitude) {
      Serial.print(lastAltitude);
    } else {
      Serial.print(F("INVALID"));
    }
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.println(F(")"));
}


static void printSpeed() {
  Serial.print(F("Speed:\t\t"));

  if (gps.speed.isValid()) {
    lastSpeed = gps.speed.kmph();
    hasSpeed = true;
    Serial.print(lastSpeed);
    Serial.println(F(" km/h"));
  } else if (hasSpeed) {
    Serial.print(lastSpeed);
    Serial.println(F(" km/h"));
  } else {
    Serial.println(F("INVALID"));
  }
}


static void printDateTime() {
  Serial.print(F("GPS Date&Time:\t"));

  if (gps.date.isValid() && gps.time.isValid()) {
    Serial.print(gps.date.year());
    Serial.print(F("-"));
    Serial.print(gps.date.month());
    Serial.print(F("-"));
    Serial.print(gps.date.day());
    Serial.print(F(" "));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    Serial.println(gps.time.second());
  } else {
    Serial.println(F("INVALID"));
  }
}

void checkGPSWiring() {
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println(F("No GPS data received: check wiring"));
  }
}
