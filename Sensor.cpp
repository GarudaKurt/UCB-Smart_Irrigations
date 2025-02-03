#include "Sensor.h"
#include <Arduino.h>

#define S1_PIN 32
#define S2_PIN 34
#define S3_PIN 35

#define relay1 15
#define relay2 17

#define MIN_DRY_VALUE 3800   // Value when sensor is dry
#define MAX_DRY_VALUE 4095

#define MIN_WET_VALUE 2000   // Value when sensor is fully submerged
#define MAX_WET_VALUE 3500


void initSensor(){
  pinMode(S1_PIN, INPUT);
  pinMode(S2_PIN, INPUT);
  pinMode(S3_PIN, INPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
}

int getMoisturePercentage(int sensorValue) {
    sensorValue = constrain(sensorValue, MIN_WET_VALUE, MAX_DRY_VALUE);
    int percentage = map(sensorValue, MIN_WET_VALUE, MAX_DRY_VALUE, 0, 100);
    return percentage;
}


int Sensor1() {
  int moistureValue = analogRead(S1_PIN);
  //return moistureValue;
  return getMoisturePercentage(moistureValue);
}

int Sensor2() {
  int moistureValue = analogRead(S2_PIN);
  //return moistureValue;
  return getMoisturePercentage(moistureValue);
}

int Sensor3() {
  int moistureValue= analogRead(S3_PIN);
  //return moistureValue;
  return getMoisturePercentage(moistureValue);
}

void waterPump1() {
  digitalWrite(relay1, HIGH);
  delay(5000);
  digitalWrite(relay1, LOW);
}

void waterPump2() {
  digitalWrite(relay2, HIGH);
  delay(8000);
  digitalWrite(relay2, LOW);
}

