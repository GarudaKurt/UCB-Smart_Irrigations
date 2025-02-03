#include <Arduino.h>
#include "configFirebase.h"
#include "Sensor.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  initFirebase();
  initSensor();
}

void loop() {
  // put your main code here, to run repeatedly:
  readSensor();
  int s1 = Sensor1();
  int s2 = Sensor2();
  int s3 = Sensor3();
  Serial.print("Sensor 1: ");
  Serial.print(s1);
  Serial.println("%");

  Serial.print("Sensor 2: ");
  Serial.print(s2);
  Serial.println("%");

  Serial.print("Sensor 3: ");
  Serial.print(s3);
  Serial.println("%");

  // if(s1 == 100)
  //   waterPump1();
  // else if(s2 == 100)
  //   waterPump2();

  delay(1000);
}
