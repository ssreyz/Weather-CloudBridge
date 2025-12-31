#include "certs.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "DHT.h"

// DHT11 pin configuration
#define SENSOR_PIN 4
#define SENSOR_TYPE DHT11

// AWS IoT topics
#define TOPIC_PUB "esp32/pub"
#define TOPIC_SUB "esp32/sub"

float temperature = 0;
float humidity = 0;

DHT dhtSensor(SENSOR_PIN, SENSOR_TYPE);
WiFiClientSecure secureClient;
PubSubClient mqttClient(secureClient);

// Function to handle incoming messages from AWS
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received message on topic: ");
  Serial.println(topic);

  StaticJsonDocument<200> jsonDoc;
  if (deserializeJson(jsonDoc, payload, length)) {
    Serial.println("Error parsing JSON");
    return;
  }

  const char* receivedMessage = jsonDoc["message"];
  if (receivedMessage) {
    Serial.println(receivedMessage);
  }
}

// Connect ESP32 to Wi-Fi and AWS IoT
void connectAWS() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");

  // Configure AWS IoT certificates
  secureClient.setCACert(AWS_CERT_CA);
  secureClient.setCertificate(AWS_CERT_CRT);
  secureClient.setPrivateKey(AWS_CERT_PRIVATE);

  mqttClient.setServer(AWS_IOT_ENDPOINT, 8883);
  mqttClient.setCallback(mqttCallback);

  Serial.println("Connecting to AWS IoT...");
  while (!mqttClient.connect(THINGNAME)) {
    Serial.print(".");
    delay(200);
  }

  mqttClient.subscribe(TOPIC_SUB);
  Serial.println("\nConnected to AWS IoT!");
}

// Publish sensor readings to AWS
void sendSensorData() {
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["temperature"] = temperature;
  jsonDoc["humidity"] = humidity;

  char payload[128];
  serializeJson(jsonDoc, payload);

  mqttClient.publish(TOPIC_PUB, payload);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  dhtSensor.begin();  // initialize DHT sensor
  connectAWS();
}

void loop() {
  humidity = dhtSensor.readHumidity();
  temperature = dhtSensor.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("DHT sensor reading failed!");
    mqttClient.loop();
    delay(2000);
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("% | Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  sendSensorData();
  mqttClient.loop();

  delay(2000); // DHT11 minimum polling interval
}
