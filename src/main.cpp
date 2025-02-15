#include <Arduino.h>


#include "L293D.h"
 
L293D l293D;


void setup() {
  Serial.begin(115200);
  Serial.println("Start app");

  l293D.AttachPinsMotor1(18, 19, 22);
  l293D.Forward(1);
  l293D.Speed(1, 90);
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

      case '?':
        Serial.println(" 1 Forwardp");
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

