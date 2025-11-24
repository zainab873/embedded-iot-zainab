

#include <WiFi.h>

const char* ssid     = "NTU FSD";
const char* password = "";

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Step 1: Scan WiFi networks
  Serial.println("Scanning WiFi networks...");

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  int count = WiFi.scanNetworks();

  if (count <= 0) {
    Serial.println("No networks found");
  } else {
    Serial.print("Found ");
    Serial.print(count);
    Serial.println(" networks:");

    for (int i = 0; i < count; i++) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.println(" dBm)");
    }
  }

  Serial.println();
  delay(2000);

  // Step 2: Connect to your WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Nothing here
}
