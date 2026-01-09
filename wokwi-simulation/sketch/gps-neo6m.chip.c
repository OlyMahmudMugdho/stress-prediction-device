// For information and examples see:
// https://link.wokwi.com/custom-chips-alpha
//
// SPDX-License-Identifier: MIT

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SECOND 1000000

// -------------------- Forward Declarations --------------------

static void chip_timer_event(void *user_data);
static void deg_to_nmea(double deg, char *out, char *hem);
static uint8_t nmea_checksum(const char *s);

// -------------------- Chip State --------------------

typedef struct {
  uart_dev_t uart0;

  uint32_t lat_attr;
  uint32_t lon_attr;
  uint32_t speed_attr;
  uint32_t enabled_attr; // float: 0.0 or 1.0
} chip_state_t;

// -------------------- Initialization --------------------

void chip_init(void) {
  setvbuf(stdout, NULL, _IOLBF, 1024);

  chip_state_t *chip = malloc(sizeof(chip_state_t));

  // Wokwi controls (ALL floats)
  chip->lat_attr     = attr_init_float("lat", -23.466417f);
  chip->lon_attr     = attr_init_float("lon", -51.840167f);
  chip->speed_attr   = attr_init_float("speed", 10.0f);
  chip->enabled_attr = attr_init_float("enabled", 1.0f);

  const uart_config_t uart_config = {
    .tx = pin_init("TX", INPUT_PULLUP),
    .rx = pin_init("RX", INPUT),
    .baud_rate = 9600,
    .user_data = chip,
  };

  chip->uart0 = uart_init(&uart_config);

  const timer_config_t timer_cfg = {
    .callback = chip_timer_event,
    .user_data = chip,
  };

  timer_t timer = timer_init(&timer_cfg);
  timer_start(timer, SECOND, true);

  printf("NEO-6M GPS chip initialized\n");
}

// -------------------- Timer Event --------------------

static void chip_timer_event(void *user_data) {
  chip_state_t *chip = (chip_state_t *)user_data;

  if (attr_read_float(chip->enabled_attr) < 0.5f) return;

  double lat   = attr_read_float(chip->lat_attr);
  double lon   = attr_read_float(chip->lon_attr);
  double speed = attr_read_float(chip->speed_attr);

  char lat_s[16], lon_s[16];
  char lat_h, lon_h;

  deg_to_nmea(lat, lat_s, &lat_h);
  deg_to_nmea(lon, lon_s, &lon_h);

  // Build sentence body (NO $ or checksum yet)
  char body[96];
  snprintf(body, sizeof(body),
    "GPRMC,123519,A,%s,%c,%s,%c,%.1f,0.0,060622,,",
    lat_s, lat_h,
    lon_s, lon_h,
    speed / 1.852   // km/h → knots
  );

  uint8_t cs = nmea_checksum(body);

  char sentence[128];
  snprintf(sentence, sizeof(sentence),
    "$%s*%02X\r\n",
    body, cs
  );

  uart_write(chip->uart0, (uint8_t *)sentence, strlen(sentence));
}

// -------------------- Helpers --------------------

static void deg_to_nmea(double deg, char *out, char *hem) {
  double v = fabs(deg);
  int d = (int)v;
  double m = (v - d) * 60.0;

  sprintf(out, "%02d%07.4f", d, m);
  *hem = (deg >= 0) ? 'N' : 'S';
}

static uint8_t nmea_checksum(const char *s) {
  uint8_t c = 0;
  while (*s) c ^= (uint8_t)*s++;
  return c;
}
