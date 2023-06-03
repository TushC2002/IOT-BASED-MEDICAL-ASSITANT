#include <Wire.h>
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "Wire.h"
#define BLYNK_TEMPLATE_ID "TMPL3c1P7fejq"
#define BLYNK_TEMPLATE_NAME "Service Robot"


char auth[] = "R0VnRJ1vFF_Cj82FO2jHzjWLnI2Ydfdt";        // You should get Auth Token in the Blynk App.
char ssid[] = "C15";                                     // Your WiFi credentials.
char pass[] = "12345678";
int s=0;
int d2=0;
// These are used to set the direction of the bridge driver.
#define re D6      //ENB
#define buzz D7      //ENB
#define m1 D0      //ENB
#define m2 D1 //IN3
#define m3 D2 //IN4
#define m4 D3 //IN1
int trigPin = D5;
int echoPin = D4;



// FORWARD
BLYNK_WRITE(V0) 
{
  int button = param.asInt(); // read button
  if (button == 1)
  {
       digitalWrite(buzz, LOW);
    digitalWrite(re, LOW);
    Serial.println("Moving forward");
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);
  }
  else {
    s=0;
    Serial.println("Stop");
    digitalWrite(m1,LOW);
    digitalWrite(m3,LOW);
    
  }
}

// RIGHT
BLYNK_WRITE(V1) 
{
  int button = param.asInt(); // read button
  if (button == 1) {
       digitalWrite(buzz, LOW);
    digitalWrite(re, LOW);
    Serial.println("Moving right");
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);
  }
  else {
    Serial.println("Stop");
         s=0;
     digitalWrite(m1,LOW);
 
    digitalWrite(m4,LOW);;
  }
}

// LEFT
BLYNK_WRITE(V2) {
     digitalWrite(buzz, LOW);
    digitalWrite(re, LOW);
  int button = param.asInt(); // read button
  if (button == 1) {
    Serial.println("Turning left");
    digitalWrite(m1,LOW);
    digitalWrite(m2,HIGH);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);
     
  }
  else {
     s=0;
    Serial.println("Stop");
    digitalWrite(m2,LOW);
    
    digitalWrite(m3,LOW);
  }
}

// BACKWARD
BLYNK_WRITE(V3)
{
  int button = param.asInt(); // read button
  if (button == 1) {
       digitalWrite(buzz, LOW);
    digitalWrite(re, LOW);
    Serial.println("Turning Back");
    digitalWrite(m1,LOW);
    digitalWrite(m2,HIGH);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);
  }
  else {
    Serial.println("Turning Stop");
    digitalWrite(m2,LOW);
      s=0;
    digitalWrite(m4,LOW);
  }
}

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(re, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
    digitalWrite(buzz,LOW);
      digitalWrite(re,LOW);
      digitalWrite(m1,LOW);
      digitalWrite(m2,LOW);
      digitalWrite(m3,LOW);
      digitalWrite(m4,LOW);
  Serial.begin(9600);

   Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() 
{
   Blynk.run();
   delay(20);
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  d2 =(duration/2)/29.1;
  delay(20);
  if((d2<=10)&&!(s))
  {
    s=1;
    digitalWrite(buzz, HIGH);
    digitalWrite(re, HIGH);
    delay(1900);
     digitalWrite(buzz, LOW);
    digitalWrite(re, LOW);
    delay(100);
}
}