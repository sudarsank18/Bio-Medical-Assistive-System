#define BLYNK_TEMPLATE_ID "TMPL3oCdhQWXb"
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN "Aa7YlFD8mjCAtGNiLoVBLD-uh89vwhMX"
#define BLYNK_PRINT Serial
#define TWILLIO_SID "" //update your TWILLIo SID in this
#define TWILLIO_AUTH "" //update your TWILLIO AUTH ID in this
#include<BlynkSimpleEsp8266.h>
#include <Adafruit_ADS1X15.h>
Adafruit_ADS1015 ads; /* Use this for the 12-bit version */
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
const char* ssid = ""; //update your wifi name in this
const char* password = ""; //update your wifi pass in this
const char* serverAddress = ""; //update your server Addr in this
const int serverPort = 8000;
const String serverName = ""; //update your server name in this
WiFiClient client;
HTTPClient http;
const int RX_pin = D5; // Define RX pin of NodeMCU
const int TX_pin = D6; // Define TX pin of NodeMCU
void setup() {
 //---------------Blynk setup--------------
 Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
 //---------wifi settings-----------
 delay(100);
 Serial.begin(9600);
 Serial.print("Connecting to ");
 Serial.println(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 //--------ADC configurations-------------
 pinMode(D5, INPUT);
 pinMode(D6, OUTPUT);
 pinMode(A0, INPUT);
 ads.setGain(GAIN_TWOTHIRDS); // 2/3x gain +/- 6.144V 1 bit = 3mV 0.1875mV (default)
 if (!ads.begin()) {
 Serial.println("Failed to initialize ADS.");
 while (1);
 }
}
String alldata;
int16_t adc0, adc1, adc2, adc3;
float volts0, volts1, volts2, volts3;
void loop() {
 int16_t
 adc0 = ads.readADC_SingleEnded(0);
 adc1 = ads.readADC_SingleEnded(1);
 adc2 = ads.readADC_SingleEnded(2);
 adc3 = ads.readADC_SingleEnded(3);
 volts0 = ads.computeVolts(adc0);
 volts1 = ads.computeVolts(adc1);
 volts2 = ads.computeVolts(adc2);
 volts3 = ads.computeVolts(adc3);
 Serial.println("-----------------------------------------------------------");
 Serial.print("AIN0: "); Serial.print(adc0); Serial.print(" "); Serial.print(volts0); Serial.println("V");
 Serial.print("AIN1: "); Serial.print(adc1); Serial.print(" "); Serial.print(volts1); Serial.println("V");
 Serial.print("AIN2: "); Serial.print(adc2); Serial.print(" "); Serial.print(volts2); Serial.println("V");
 Serial.print("AIN3: "); Serial.print(adc3); Serial.print(" "); Serial.print(volts3); Serial.println("V");
 http.end();
 delay(300);
 if(adc0 < 200 && adc1 >= 190 && adc2 >= 190 && adc3 >= 190){
 Blynk.virtualWrite(V0, "Need water");
 }
 else if(adc1 < 200 && adc0 > 180 && adc2 > 190 && adc3 > 190){
 Blynk.virtualWrite(V0, "I'm hungry. Can you prepare something for me to eat?");
 }
 else if(adc2 < 200 && adc1 > 180 && adc3 > 180 && adc0 > 180){
 Blynk.virtualWrite(V0, "I feel sick check me pls");
 }
 else if(adc3 < 200 && adc1 > 180 && adc2 > 180 && adc0 > 180){
 Blynk.virtualWrite(V0, "I need help using the restroom");
 }
 else if(adc3 < 200 && adc2 < 200 && adc1 > 175 && adc0 > 175){
 Blynk.virtualWrite(V0, "Could you read this book for me");
 }
 else if(adc2 < 200 && adc1 < 200 && adc3 > 175 && adc0 > 175)
 {
 Blynk.virtualWrite(V0, "I need my medication. Can you help me with it?");
 }
 else if(adc0 < 200 && adc1 < 200 && adc2 > 175 && adc3 > 175){
 Blynk.virtualWrite(V0, "I'd like to listen to some music. Can you play some for me?");
 }
 else if(adc0 < 200 && adc1 < 200 && adc2 < 200 && adc3 < 200)
 {
 Blynk.logEvent("patient", String("EMERGENCY!! patient has collapsed"));
 }
 else{
 Blynk.virtualWrite(V0, " ");
 }
 Blynk.run();
}