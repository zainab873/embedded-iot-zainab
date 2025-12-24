/****************************************************
 * ESP32 + DHT22 + MQTT (PUBLISHER ONLY)
 * Publishes:
 *   home/lab1/hum
 ****************************************************/

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// ---------- WiFi ----------
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// ---------- MQTT ----------
const char* mqtt_server = "192.168.18.13";  // Mosquitto / Cloud broker
const int   mqtt_port   = 1883;

// Topic for humidity only
const char* TOPIC_HUM = "home/lab1/hum";

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
    if (mqtt.connect("publisher-2")) {  // Unique client ID
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

  float humidity = dht.readHumidity();

  if (isnan(humidity)) {
    Serial.println("DHT read failed");
    delay(2000);
    return;
  }

  char hBuf[8];
  dtostrf(humidity, 4, 2, hBuf);

  mqtt.publish(TOPIC_HUM, hBuf);

  Serial.print("Published -> Hum: ");
  Serial.print(hBuf);
  Serial.println(" %");

  delay(5000);  // publish every 5 seconds
}
