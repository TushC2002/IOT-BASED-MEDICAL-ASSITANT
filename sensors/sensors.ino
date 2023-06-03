#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "Wire.h"
#define REPORTING_PERIOD_MS 1000
#define BLYNK_TEMPLATE_ID "TMPL3c1P7fejq"
#define BLYNK_TEMPLATE_NAME "Service Robot"


char auth[] = "R0VnRJ1vFF_Cj82FO2jHzjWLnI2Ydfdt";       // You should get Auth Token in the Blynk App.
char ssid[] = "C15";                                     // Your WiFi credentials.
char pass[] = "12345678";           // You should get Auth Token in the Blynk App.

 
// Connections : SCL PIN - D1 , SDA PIN - D2 , INT PIN - D0
PulseOximeter pox;
 
float BPM, SpO2;
uint32_t tsLastReport = 0;

void onBeatDetected()
{
    Serial.println("Beat Detected!");
 float temperature = analogRead(A0);
 temperature = (temperature*19);
  Blynk.virtualWrite(V5, temperature);
  Serial.print("temp :");  Serial.println(temperature);
}
 
void setup()
{
    Serial.begin(115200);
    
    
    pinMode(16, OUTPUT);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
 
    Serial.print("Initializing Pulse Oximeter..");
 
    if (!pox.begin())
    {
         Serial.println("FAILED");
       
         for(;;);
    }
    else
{
         Serial.println("SUCCESS");
         pox.setOnBeatDetectedCallback(onBeatDetected);
    }
 
   
}
 
void loop()
{
   pox.update();
   Blynk.run();
    //float temperature = analogRead(A0);
   //temperature = (temperature/1023)*3300;
    BPM = pox.getHeartRate();
    SpO2 = pox.getSpO2();
     if (millis() - tsLastReport > REPORTING_PERIOD_MS)
    {
        Blynk.virtualWrite(V6, BPM);
        Blynk.virtualWrite(V4, SpO2);
         //Blynk.virtualWrite(V6, temperature);
          tsLastReport = millis();
    }
}
