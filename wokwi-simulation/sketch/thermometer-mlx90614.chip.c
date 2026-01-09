#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

// Global variables
uint8_t current_reg = 0;
uint8_t read_count = 0;
uint32_t ambient_temp_attr;
uint32_t object_temp_attr;

// Callback functions
static bool on_connect(void* user_data, uint32_t address, bool rw) {
  return true; // Always acknowledge
}

static bool on_write(void* user_data, uint8_t data) {
  current_reg = data;
  read_count = 0;
  return true; // ACK
}

static uint8_t on_read(void* user_data) {
  float T_celsius;
  if (current_reg == 0x06) {
    T_celsius = attr_read_float(ambient_temp_attr);
  } else if (current_reg == 0x07) {
    T_celsius = attr_read_float(object_temp_attr);
  } else {
    return 0; // Unsupported register
  }

  float T_kelvin = T_celsius + 273.15f;
  uint16_t raw_value = (uint16_t)(T_kelvin * 50.0f + 0.5f);
  uint8_t low_byte = raw_value & 0xFF;
  uint8_t high_byte = (raw_value >> 8) & 0xFF;

  if (read_count == 0) {
    read_count++;
    return low_byte;
  } else if (read_count == 1) {
    read_count++;
    return high_byte;
  } else {
    return 0;
  }
}

static void on_disconnect(void* user_data) {
  // No action needed
}

// Initialize the chip
void chip_init() {
  pin_t scl = pin_init("SCL", INPUT_PULLUP);
  pin_t sda = pin_init("SDA", INPUT_PULLUP);

  // Initialize attributes
  ambient_temp_attr = attr_init_float("ambient_temp", 25.0f);
  object_temp_attr = attr_init_float("object_temp", 25.0f);

  i2c_config_t config = {
    .scl = scl,
    .sda = sda,
    .address = 0x5A,
    .connect = on_connect,
    .read = on_read,
    .write = on_write,
    .disconnect = on_disconnect,
    .user_data = NULL,
  };

  i2c_init(&config);
}