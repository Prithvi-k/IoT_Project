#include <Servo.h>
//defining Servos
Servo servohori;
int servoh = 90;
int servohLimitHigh = 160;
int servohLimitLow = 20;

Servo servoverti; 
int servov = 90; 
int servovLimitHigh = 160;
int servovLimitLow = 20;
//Assigning LDRs
int ldrtopr = 34; // top right LDR yellow
int ldrtopl = 35; // top left LDR green
int ldrbotl = 32; // bottom left LDR blue
int ldrbotr = 33; // bottom right LDR orange

 void setup () 
 {
  Serial.begin(9600);
  pinMode(ldrtopl, INPUT);
  pinMode(ldrtopr, INPUT);
  pinMode(ldrbotl, INPUT);
  pinMode(ldrbotr, INPUT);
  // servohori.attach(18); 18 -->36
  // servoverti.attach(14); 14 -->39
  servohori.attach(18);
  servoverti.attach(14);
  // servohori.write(90);
  // servoverti.write(90);
  delay(500);
 }

void loop()
{
  servoh = servohori.read();
  servov = servoverti.read();
  //capturing analog values of each LDR
  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);
  // Serial.print(topl, DEC);
  Serial.print(topl, DEC);
  Serial.print(" ");
  Serial.print(topr, DEC);
  Serial.print(" ");
  Serial.print(botl, DEC);
  Serial.print(" ");
  Serial.print(botr, DEC);
  Serial.print(" \n");

  // calculating average
  int avgtop = (topl + topr) / 2; //average of top LDRs
  int avgbot = (botl + botr) / 2; //average of bottom LDRs
  int avgleft = (topl + botl) / 2; //average of left LDRs
  int avgright = (topr + botr) / 2; //average of right LDRs


  if (avgtop < avgbot)
  {
    servoverti.write(servov +1);
    if (servov > servovLimitHigh) 
    { 
      servov = servovLimitHigh;
    }
    delay(10);
  }
  else if (avgbot < avgtop)
  {
    servoverti.write(servov -1);
    if (servov < servovLimitLow)
    {
      servov = servovLimitLow;
    }
    delay(10);
  }
  else 
  {
    servoverti.write(servov);
  }
  
  if (avgleft > avgright)
  {
    servohori.write(servoh -1);
    if (servoh > servohLimitHigh)
    {
      servoh = servohLimitHigh;
    }
    delay(10);
  }
  else if (avgright > avgleft)
  {
    servohori.write(servoh + 1);
    // Serial.println("Hi");
    if (servoh < servohLimitLow)
    {
      servoh = servohLimitLow;
    }
    delay(10);
  }
  else 
  {
    servohori.write(servoh);
  }
  delay(50);
}