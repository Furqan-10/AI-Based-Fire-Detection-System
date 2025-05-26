#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

// WiFi credentials
//const char* ssid = "CM Laptop Program";
//const char* password = "Pakistan@786";
const char* ssid = "Asif Hameed";
const char* password = "77771010";

// Hugging Face Space endpoint
const char* serverName = "https://fuqi-10-fired.hf.space/predict";

// Hardware
const int buzzerPin = 23;  // Active buzzer on GPIO23
#define RXp2 16
#define TXp2 17

// Variables for non-blocking operation
unsigned long previousMillis = 0;
const long interval = 500;  // Check serial every 500ms
String serialBuffer = "";

void setup() {
  Serial.begin(115200);     // Debug output
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);      
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Connected to WiFi!");
}

void loop() {
  // Non-blocking serial reading
  while (Serial2.available() > 0) {
    char c = Serial2.read();
    if (c == '\n') {
      processTemperature(serialBuffer);
      serialBuffer = "";
    } else {
      serialBuffer += c;
    }
  }

  // Non-blocking WiFi status check
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected. Reconnecting...");
    WiFi.reconnect();
    delay(1000);
  }
}

void processTemperature(String tempStr) {
  float temperature = tempStr.toFloat();
  Serial.print("Received temperature: ");
  Serial.println(temperature);

  if (WiFi.status() == WL_CONNECTED) {
    sendToCloud(temperature);
  }
}

void sendToCloud(float temperature) {
  WiFiClientSecure *client = new WiFiClientSecure;
  if (client) {
    client->setInsecure();
    HTTPClient https;
    
    if (https.begin(*client, serverName)) {
      https.addHeader("Content-Type", "application/json");
      String jsonData = "{\"temperature\":" + String(temperature) + "}";
      
      Serial.println("Sending: " + jsonData);
      int httpCode = https.POST(jsonData);
      
      if (httpCode == 200) {
        String response = https.getString();
        Serial.println("Response: " + response);
        
        if (response.indexOf("\"prediction\":1") >= 0) {
          triggerBuzzer();
        }
      } else {
        Serial.println("HTTP Error: " + String(httpCode));
      }
      https.end();
    }
    delete client;
  }
}

void triggerBuzzer() {
  digitalWrite(buzzerPin, HIGH);
  delay(1000);  // Buzzer on for 1 second
  digitalWrite(buzzerPin, LOW);
}