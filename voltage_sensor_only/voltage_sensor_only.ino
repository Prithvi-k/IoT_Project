const int voltage_analog_pin= 14;
int voltage_adc = 0, voltage_value = 0, voltage_count = 0;
float voltage_avg = 0.0;
void setup() 
{
  Serial.begin(9600);
}
void loop() 
{
  voltage_adc = analogRead(voltage_analog_pin);
  // Serial.println(voltage_adc);
  float v=((voltage_adc * 0.004450) + 0.06588);
  if(v == 0.07)
  {
    v = 0.00;
  }
  voltage_avg += v;
  voltage_count++;
  if(voltage_count == 10)
  {
    voltage_avg /= 10;
    Serial.println(voltage_avg);
    voltage_count = 0;
    voltage_avg = 0.0;
  }
  delay(200);
}