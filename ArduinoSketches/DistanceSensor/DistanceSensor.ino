
/**
 * This Sketch is based on the MySensors Distance Sensor Sketch
 * https://github.com/mysensors/MySensorsArduinoExamples/tree/master/examples/DistanceSensor
 *
 * Original Headers:
 * Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
 * Copyright (C) 2013-2015 Sensnology AB
 * Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
 *
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 *******************************
 *
 * REVISION HISTORY
 * Version 1.0 - Henrik EKblad
 * Version 1.1 - Alex Muthmann - https://dev-eth0.de
 *
 * DESCRIPTION
 * This sketch provides an example how to implement a distance sensor using HC-SR04.
 * http://www.mysensors.org/build/distance
 */


// Enable debug prints to serial monitor
#define MY_DEBUG

// Enable and select radio type attached
#define MY_RADIO_NRF24
#define MY_RF24_CE_PIN 9
#define MY_RF24_CS_PIN 10

// Sleep time between reads (in milliseconds)
unsigned long SLEEP_TIME = 3000;


#include <Wire.h>
#include <SPI.h>
#include <MySensors.h>
#include <NewPing.h>


// Pins used for the Sensors
#define TRIGGER_PIN  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int lastDist  = -1;

// ID used
#define CHILD_ID 13


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
MyMessage msg(CHILD_ID, V_DISTANCE);



void setup()
{
  
}

void presentation() {
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo("Distance Sensor", "1.1");

  // Register all sensors to gw
  present(CHILD_ID, S_DISTANCE);
}

void loop()
{
  // Ping 5 times and calculate median
  int dist_ms = sonar.ping_median(5);
  Serial.print(dist_ms);
  // Calculate actual distance
  int dist = sonar.convert_cm(dist_ms);
  Serial.print("Distance = ");
  Serial.print(dist);
  Serial.println(" cm");
  if (dist != lastDist) {
      send(msg.set(dist));
      lastDist = dist;
  }

  sleep(SLEEP_TIME);
}


