#include "OneWire/OneWire.h"
#include "spark-dallas-temperature/spark-dallas-temperature.h"
#include <math.h>

OneWire ds(D3);
DallasTemperature sensors(&ds);

double pressure = 0;
double temperature = 0;

unsigned long last_executed;

void ledOff() {
  RGB.color(32,32,32);
}

void ledOn(int r, int g, int b) {
  RGB.color(r, g, b);
}

void setup() {
  setADCSampleTime(ADC_SampleTime_13Cycles5);
  Serial.begin(9600);  // local hardware test only
  pinMode(A7, INPUT);

  delay(1000);
  sensors.begin();

  Spark.variable("temperature", &temperature, DOUBLE);
  Spark.variable("pressure", &pressure, DOUBLE);

  RGB.control(true);
  RGB.brightness(8);
  ledOff();

  last_executed = millis();
}

double map(const double & x,
           const double & in_min, const double & in_max,
           const double & out_min, const double & out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop() {
  unsigned long loop_time = millis();
  if ((loop_time - last_executed) >= 2000)
  {
    ledOn(0,255,0);
    sensors.requestTemperatures();
    temperature = sensors.getTempCByIndex(0);
    pressure = (double)analogRead(A7);
    Serial.print(pressure, 0);
    //Serial.print(" raw");
    Serial.print(", ");
    Serial.print(map(pressure, 0.0, 4095.0, 0.0, 1.0), 4);
    //Serial.print(" norm");
    Serial.print(", ");
    double v = map(pressure, 0.0, 4095.0, 0.0, 3.3);
    Serial.print(v, 4);
    //Serial.print(" V");
    Serial.print(", ");
    Serial.print(map(v, 0.6, 3.0, 0.0, 4.0), 4);
    //Serial.print(" kPa");
    Serial.print("\n");
    ledOff();
    last_executed = loop_time;
  }
}
