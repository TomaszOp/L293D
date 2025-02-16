#include <Arduino.h>


#include "L293D.h"
 
L293D l293D;


void setup() {
  Serial.begin(115200);
  Serial.println("Start app");

  l293D.AttachPinsMotor1(13, 12, 22);
  l293D.AttachPinsMotor2(14, 27, 23);
  l293D.Forward(1);
  l293D.Forward(2);

  l293D.Speed(1, 90);
  l293D.Speed(2, 90);
}

void loop() 
{
  delay(30);  

  if (Serial.available() > 0)
  {
    char key = Serial.read();

    switch (key)
    {
      case '1':
        l293D.Forward(1);
        break;
      case '2':
        l293D.Backwards(1);
        break;

     case '3':
        l293D.Forward(2);
        break;
      case '4':
        l293D.Backwards(2);
        break;
      
      case 's':
        l293D.Stop(1);
        break;

      case 'b':
        l293D.Braking(1);
        break;

      case '[':
        l293D.Speed(1, 100);
        break;

      case ']':
        l293D.Speed(1, 50);
        break;

      case 't':
        for(int i = 0 ; i < 100; i = i+10)
        {
          Serial.println(i);
          l293D.Speed(1, i);
          delay(500); 
        }
        break;

      case 'y':
        for(int i = 0 ; i < 100; i = i+10)
        {
          Serial.println(i);
          l293D.Speed(2, i);
          delay(500); 
        }
        break;


      case '?':
        Serial.println(" 1 Forward");
        Serial.println(" 2 Backwards");        
        Serial.println(" s Stop");
        Serial.println(" b Braking");
        Serial.println(" [ Speed 1");
        Serial.println(" ] Speed 2");
        break;

      default:
        break;
    }
  }

}

