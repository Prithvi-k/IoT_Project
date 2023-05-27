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
  // Serial.println(ADC_VALUE);
  // Serial.print("ADC VALUE = ");
  // Serial.println(ADC_VALUE);
  // delay(1000);
  // float voltage_value = (ADC_VALUE * 3.3 ) / (4095.0);
  float v=(ADC_VALUE*5000)/5860.0;
        float cur=v-2500;//2470.345;
        cur/=1000;
  // Serial.print("Current = ");
  // Serial.println(cur);
  // Serial.print(" Amphere");
  // delay(1000);
  // float current=(ADC_VALUE*5)/1023.0;
  // current=(current-8.96)/0.185;
  Serial.println(cur);

  // float current=ADC_VALUE-2930;
  // current=current*5/4905
  delay(1000);
}