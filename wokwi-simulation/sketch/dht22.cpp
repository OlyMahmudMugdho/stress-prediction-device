#include <DHT.h>
#include <Arduino.h>
#include "dht22.h"

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

static float lastTemp = 0;
static float lastHumidity = 0;

void setupDHT22() {
  dht.begin();
}

void readDHT22() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (!isnan(h)) lastHumidity = h;
  if (!isnan(t)) lastTemp = t;
}

void displayDHT22() {
  Serial.print("DHT22 Temp: ");
  Serial.print(lastTemp);
  Serial.print(" °C | Humidity: ");
  Serial.print(lastHumidity);
  Serial.println(" %");
}
