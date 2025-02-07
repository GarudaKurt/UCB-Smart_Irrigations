#include "Sensor.h"
#include <Arduino.h>

#define S1_PIN 32 //D32
#define S2_PIN 34 //D34
#define S3_PIN 35 //D35

#define ledS1 2  //D2
#define ledS2 4  //D4
#define ledS3 16 //D16

#define relay1 15 //D15
#define relay2 17 //D17


#define MIN_DRY_VALUE 3800   // Value when sensor is dry
#define MAX_DRY_VALUE 4095

void initSensor(){
  pinMode(S1_PIN, INPUT);
  pinMode(S2_PIN, INPUT);
  pinMode(S3_PIN, INPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(ledS1, OUTPUT);
  pinMode(ledS2, OUTPUT);
  pinMode(ledS3, OUTPUT);
  digitalWrite(relay1, LOW);
  digitalWrite(ledS1, LOW);
  digitalWrite(ledS2, LOW);
  digitalWrite(ledS3, LOW);
}

//50-70 %  dry percentage value but in the analog read it was around 3800 min and max 4095
//0% wet dry percentage value the reading of the analog is around less than 3400 to 1000
int getMoisturePercentage(int sensorValue) {
  int percentage = 0;
  if(sensorValue >= MIN_DRY_VALUE && sensorValue <= MAX_DRY_VALUE)
    percentage = random (50,70);
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
  digitalWrite(ledS1, HIGH);
  delay(2000);
  digitalWrite(relay1, LOW);
  digitalWrite(ledS1, LOW);
}

void waterPump2() {
  digitalWrite(relay2, HIGH);
  digitalWrite(ledS2, HIGH);
  delay(2000);
  digitalWrite(relay2, LOW);
  digitalWrite(ledS2, LOW);
}

void ledState_On() {
  digitalWrite(ledS3, HIGH);
}
void ledState_Off() {
  digitalWrite(ledS3, LOW);
}

