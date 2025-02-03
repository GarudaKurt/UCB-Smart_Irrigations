#include "configFirebase.h"
#include <Arduino.h>
#include "Sensor.h"

#ifdef ESP32
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <WiFiUdp.h>
#endif

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "teloy" //change this based on your mobile hotspot name and make sure to set 2.4Ghz your mobile hotspot
#define WIFI_PASSWORD "Tyler_property#0124" //change this  based on youe hotspot password
#define API_KEY "AIzaSyBjhAuT0ozWZRXIEYXg3x97f6vAHJaKU5c"
#define DATABASE_URL "https://ucb-smart-irrigation-default-rtdb.firebaseio.com/"
#define USER_EMAIL "smartirrigations@gmail.com" //create OAuth user email
#define USER_PASSWORD "smartirrigations" //create OAuth user password

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

int timeZone = 8 * 3600;  // Philippine Time
int dst = 0;

void initFirebase() {

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connected to WiFi, please check!");
    delay(300);
  }

  configTime(timeZone, dst, "pool.ntp.org","time.nist.gov");
  Serial.println("Waiting for time....");
  while(!time(nullptr)){
    Serial.println("Time is nullptr!");
    delay(1000);
  }

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;
  Firebase.reconnectWiFi(true);
  Firebase.begin(&config, &auth);
  Firebase.setDoubleDigits(5);
}

void readSensor() {
  if (Firebase.ready()) {
    bool success1 = Firebase.setInt(fbdo, "/monitoring/s1", Sensor1());
    bool success2 = Firebase.setInt(fbdo, "/monitoring/s2", Sensor2());
    bool success3 = Firebase.setInt(fbdo, "/monitoring/s3", Sensor3());
    Serial.print("S1 Val: ");
    Serial.println(Sensor1());
    Serial.print("S2 Val: ");
    Serial.println(Sensor2());
    Serial.print("S3 Val: ");
    Serial.println(Sensor3());
    if(!success1 || !success2 || !success3)
      Serial.println("Failed to send to firebase");
  }
}


const char* getTime() {
  static char buffer[10];
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  snprintf(buffer, sizeof(buffer), "%02d:%02d", p_tm->tm_hour, p_tm->tm_min);
  return buffer;
}

const char* getDate() {
  static char buffer[10];
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  snprintf(buffer, sizeof(buffer), "%02d/%02d", p_tm->tm_mday, p_tm->tm_mon + 1);
  return buffer;
}