const int analog_channel_pin= 14;
int ADC_VALUE = 0;
int voltage_value = 0;
void setup() 
{
  Serial.begin(9600);
}
void loop() 
{
  ADC_VALUE = analogRead(analog_channel_pin);
  Serial.println(ADC_VALUE);
  // Serial.print("ADC VALUE = ");
  // Serial.println(ADC_VALUE);
  // delay(1000);
  // float voltage_value = (ADC_VALUE * 3.3 ) / (4095.0);
  float v=(ADC_VALUE)*(ADC_VALUE*-9.66631*1e-7+0.0054736);
  Serial.println(v);
  delay(1000);
}