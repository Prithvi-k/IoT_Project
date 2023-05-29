// PINS USED
// bmp -> 22(SCL), 21(SDA)
// voltage -> 32
// current 1 -> 33
// current 2 -> 34
// dht - 35

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include "Adafruit_Sensor.h"
// #include <DHT.h>
// #include <DHT_U.h>
// #include "DHT.h"

// #define DHTTYPE DHT11
// #define dht_dpin 35

// DHT dht(dht_dpin, DHTTYPE);

int master_count = 0, debug_count = 0;
Adafruit_BMP280 bmp; // use I2C interface
int cur1_pin = 33, cur2_pin = 34;
float cur1_avg = 0.0, cur2_avg = 0.0;
float sum_t = 0, sum_p = 0, sum_a = 0, mean_t = 0, mean_p = 0, mean_a = 0;
const int voltage_analog_pin= 32;
int voltage_adc = 0, voltage_count = 0;
float voltage_avg = 0.0, sum_humidity = 0.0, humidity_avg = 0.0;

void setup() {
  // put your setup code here, to run once:
  bmp.begin(0x76);
  Serial.begin(9600);
  pinMode(cur1_pin,INPUT);
  pinMode(cur2_pin,INPUT);
  // dht.begin();
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  master_count++;
  // debug_count++;

  if(master_count == 10)
  {
    mean_t = sum_t / 10.0;
    Serial.print("Temperature: ");
    Serial.println(mean_t);
    sum_t = 0.0;
    
    mean_p = sum_p / 10.0;
    Serial.print("Pressure: ");
    Serial.println(mean_p/100);
    sum_p = 0.0;

    mean_a = sum_a / 10.0;
    Serial.print("Altitude: ");
    Serial.println(mean_a);
    sum_a = 0.0;

    // humidity_avg = sum_humidity / 10.0;
    // Serial.print("Humidity: ");
    // Serial.println(humidity_avg);
    // sum_humidity = 0.0;
    
    cur1_avg = cur1_avg / 10.0;
    Serial.print("Current 1: ");
    Serial.println(cur1_avg);
    cur1_avg = 0.0;

    cur2_avg = cur2_avg / 10.0;
    // Serial.print("Current 2: ");
    // Serial.println(cur2_avg);
    cur2_avg = 0.0;

    voltage_avg /= 10;
    Serial.print("Voltage: ");
    Serial.println(voltage_avg);
    voltage_count = 0;
    voltage_avg = 0.0;

    master_count = 0;
    Serial.println("");
    Serial.println("");
    Serial.println("");
  }

  // if(debug_count == 10)
  // {
  //   // voltage_avg /= 10;
  //   // Serial.print("Voltage: ");
  //   // Serial.println(voltage_avg);
  //   // debug_count = 0;
  // }

  float temp = bmp.readTemperature();
  sum_t = sum_t + temp;

  float pressure = bmp.readPressure();
  sum_p = sum_p + pressure;

  float altitude = bmp.readAltitude();
  sum_a = sum_a + altitude;

  // float humidity = dht.readHumidity();
  // // Serial.println(humidity);
  // sum_humidity = sum_humidity + humidity;

  int cur1_adc=analogRead(cur1_pin);
  float cur1_current = (cur1_adc * -0.002246) + 6.499;
  cur1_avg += cur1_current;

  int cur2_adc=analogRead(cur2_pin);
  // Debugging
  // Serial.println(cur2_adc);
  float cur2_current = (cur2_adc * 0.003842) - 4.491;
  cur2_avg += cur2_current;

  voltage_adc = analogRead(voltage_analog_pin);
  // Debugging
  // Serial.println(voltage_adc);
  float v=((voltage_adc * 0.004150) + 0.7190);
  if(v == 0.7190)
  {
    v = 0.00;
  }
  voltage_avg += v;
  voltage_count++;
  delay(200);
}
