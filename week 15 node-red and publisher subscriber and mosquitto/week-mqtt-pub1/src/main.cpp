/****************************************************
 * ESP32 + DHT22 + MQTT (PUBLISHER ONLY)
 * Publishes:
 *   home/lab1/temp
 ****************************************************/

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// ---------- WiFi ----------
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// ---------- MQTT ----------
const char* mqtt_server = "192.168.137.1";  // Mosquitto / Cloud broker
const int   mqtt_port   = 1883;

// Topic for temperature only
const char* TOPIC_TEMP = "home/lab1/temp";

// ---------- DHT ----------
#define DHTPIN  23
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ---------- MQTT Client ----------
WiFiClient espClient;
PubSubClient mqtt(espClient);

// ---------- Functions ----------
void connectWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void connectMQTT() {
  while (!mqtt.connected()) {
    Serial.print("Connecting to MQTT...");
    if (mqtt.connect("publisher-1")) {  // Unique client ID
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.println(mqtt.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  connectWiFi();

  mqtt.setServer(mqtt_server, mqtt_port);
  connectMQTT();
}

void loop() {
  if (!mqtt.connected()) {
    connectMQTT();
  }
  mqtt.loop();

  float temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("DHT read failed");
    delay(2000);
    return;
  }

  char tBuf[8];
  dtostrf(temperature, 4, 2, tBuf);

  mqtt.publish(TOPIC_TEMP, tBuf);

  Serial.print("Published -> Temp: ");
  Serial.print(tBuf);
  Serial.println(" C");

  delay(5000);  // publish every 5 seconds
}
