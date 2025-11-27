// Zainab Sultan
// 23-NTU-CS-1097
// BSCS - 5B

#include <WiFi.h>

const char* ssid = "iPhone";
const char* password = "123456789";             

IPAddress local_IP(172, 20, 10, 7);
IPAddress gateway(172, 20, 10, 1);
IPAddress subnet(255, 255, 255, 0);    
IPAddress primaryDNS(172, 20, 10, 1);
IPAddress secondaryDNS(8, 8, 8, 8);

WiFiServer server(80);
const int LED_PIN = 2;    // Built-in LED

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Static IP config failed (WiFi.config returned false)");
    
  }

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);  

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 20000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Serial.print("ESP32 IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect within timeout. Status:");
    Serial.println(WiFi.status());
  }

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  Serial.println("New Client connected");
  // read the first line (request line)
  String request = client.readStringUntil('\n');
  request.trim();                // remove \r and whitespace
  Serial.println("Request: " + request);

  if (request.indexOf("GET /LED=ON") != -1) {
    digitalWrite(LED_PIN, HIGH);
  } else if (request.indexOf("GET /LED=OFF") != -1) {
    digitalWrite(LED_PIN, LOW);
  }

  String htmlPage =
    "<!DOCTYPE html><html>"
    "<head><meta charset='utf-8'><title>ESP32 LED</title></head>"
    "<body><h1>ESP32 LED Control</h1>"
    "<p><a href=\"/LED=ON\"><button>LED ON</button></a></p>"
    "<p><a href=\"/LED=OFF\"><button>LED OFF</button></a></p>"
    "</body></html>";

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(htmlPage);

  delay(1);
  client.stop();
  Serial.println("Client disconnected");
}