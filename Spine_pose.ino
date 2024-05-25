#define BLYNK_TEMPLATE_ID "TMPL3oCdhQWXb"
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN "Aa7YlFD8mjCAtGNiLoVBLD-uh89vwhMX"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define ADXL345_ADDRESS (0x53)
const int heartRatePin = A0;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
const char* ssid = ""; // Replace with your WiFi SSID
const char* password = ""; // Replace with your WiFi password
char auth[] = BLYNK_AUTH_TOKEN;
BlynkTimer timer;
void notifyPosition(float x, float y, float z) {
 if (x >= -0.50 && x <= 1.50 && y >= 7 && y <= 8.5 && z >= 7 && z <= 8) {
 Blynk.virtualWrite(V2, "You are straight in position, Good!");
 } else if (x >= -0.0 && x <= 1 && y >= -3 && y <= 6 && z >= 9 && z <= 10) {
 Blynk.virtualWrite(V2, "Sit straight, your spine is in a bend position");
 }
 else {
 Blynk.virtualWrite(V2, "Relax, your spine is normal");
 }
}
void setup() {
 Serial.begin(9600);
 while (!Serial); // Wait for Serial Monitor to open
 Serial.println("Initializing ADXL345 accelerometer...");
 if (!accel.begin(ADXL345_ADDRESS)) {
 Serial.println("Error initializing ADXL345 sensor. Check your connections!");
 while (1); // Loop indefinitely
 }
 Serial.println("ADXL345 sensor initialized successfully!");
 Serial.println();
 Serial.println("Connecting to WiFi...");
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected!");
 Serial.print("IP Address: ");
 Serial.println(WiFi.localIP());
 Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
 timer.setInterval(1000L, sendSensor);
}
void sendSensor() {
 sensors_event_t event;
 accel.getEvent(&event);

 Serial.print("X: ");
 Serial.print(event.acceleration.x);
 Serial.print(" Y: ");
 Serial.print(event.acceleration.y);
 Serial.print(" Z: ");
 Serial.print(event.acceleration.z);
 Serial.println(" m/s^2");

 notifyPosition(event.acceleration.x, event.acceleration.y, event.acceleration.z);
 int heartRateValue = analogRead(heartRatePin); // Read analog value from sensor
 int heartRate = map(heartRateValue, 0, 1023, 0, 200);
 Serial.print("Heart Rate Value: ");
 Serial.println(heartRate);
 Blynk.virtualWrite(V1, heartRate);

 if (heartRate <= 70) {
 Blynk.virtualWrite(V3, "Heart rate is low!");
 } else if (heartRate > 70 && heartRate <= 120) {
 Blynk.virtualWrite(V3, "Heart rate is normal.");
 } else {
 Blynk.virtualWrite(V3, "Heart rate is abnormal, emergency!");
 }
}
void loop() {
 Blynk.run();
 timer.run();
}