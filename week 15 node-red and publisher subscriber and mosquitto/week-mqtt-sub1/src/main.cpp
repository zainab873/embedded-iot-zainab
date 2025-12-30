/****************************************************
 * ESP32 + MQTT Subscriber + OLED (Temp & Humidity)
 * Subscribes: home/lab1/temp, home/lab1/hum
 * Displays both on SSD1306 OLED
 ****************************************************/

#include <WiFi.h>
#include <PubSubClient.h> 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------- WiFi ----------
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// ---------- MQTT ----------
const char* mqtt_server = "192.168.137.1"; // MQTT broker IP
const int mqtt_port = 1883;

const char* TOPIC_TEMP = "home/week15/temp";
const char* TOPIC_HUM  = "home/week15/hum";

// ---------- OLED ----------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---------- MQTT ----------
WiFiClient espClient;
PubSubClient mqtt(espClient);

// Latest sensor values
String lastTemp = "--";
String lastHum  = "--";

// Function to update OLED display
void showData() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("MQTT Temp & Hum Monitor");
  display.println("----------------------");

  display.setCursor(0, 25);
  display.print("Temp: ");
  display.print(lastTemp);
  display.println(" C");

  display.setCursor(0, 45);
  display.print("Hum : ");
  display.print(lastHum);
  display.println(" %");

  display.display();
}

// MQTT callback: runs when message arrives
void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];
  msg.trim();

  if (String(topic) == TOPIC_TEMP) {
    lastTemp = msg;    // from Pub1
    Serial.print("Temp received: ");
    Serial.println(lastTemp);
  } 
  else if (String(topic) == TOPIC_HUM) {
    lastHum = msg;     // from Pub2
    Serial.print("Hum received: ");
    Serial.println(lastHum);
  }

  showData();          // update OLED
}

void connectWiFi() {
  Serial.print("Connecting WiFi");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

// Connect to MQTT broker as subscriber
void connectMQTT() {
  while (!mqtt.connected()) {
    Serial.print("Connecting MQTT...");
    if (mqtt.connect("subscriber-1")) {   // Unique client ID
      Serial.println("connected");
      mqtt.subscribe(TOPIC_TEMP);
      mqtt.subscribe(TOPIC_HUM);
      showData();
    } else {
      Serial.print("failed rc=");
      Serial.println(mqtt.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // OLED init (ESP32 default: SDA=21, SCL=22)
  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
    while (true) delay(3);
  }
  display.clearDisplay();
  display.display();

  showData();       // initial screen
  connectWiFi();

  mqtt.setServer(mqtt_server, mqtt_port);
  mqtt.setCallback(callback);
  connectMQTT();
}

void loop() {
  if (!mqtt.connected()) connectMQTT();
  mqtt.loop(); 
}
