/**
 * Part 1 — System Entry (Login / Startup / Online)
 * Team10 — Smart Home Security Monitor
 *
 * Web demo login (admin/smarthome123) lives in presentation/auth.js (JavaScript).
 * On ESP32, "system entry" = WiFi + MQTT connect + online status publish.
 */
#include <Arduino.h>
#include "config.h"
#include "sensor_manager.h"
#include "mqtt_publisher.h"

extern SensorManager sensors;
extern MqttPublisher mqtt;

bool calibrationDone = false;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("=== ESP32 Smart Home Security Monitor ===");
  Serial.println("=== Team10 — System entry ===");

  sensors.begin();
  mqtt.begin();   // WiFi + MQTT broker connection

  Serial.println("[Setup] Calibrating MQ-2 — keep sensor in clean air for 5 seconds...");
  delay(5000);
  sensors.calibrateMq2();
  calibrationDone = true;

  mqtt.publishStatus("online");   // smarthome/living-room/status
  Serial.println("[Setup] Ready — publishing telemetry every 5 s");
}
