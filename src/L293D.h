#ifndef _L293D_H_
#define _L293D_H_

#include <Arduino.h>

#define LEDC_CHANNEL_0  0
#define LEDC_CHANNEL_1  1
#define LEDC_CHANNEL_2  2
#define LEDC_CHANNEL_3  3

#define DEFAULT_CHANNEL1  LEDC_CHANNEL_0
#define DEFAULT_CHANNEL2  LEDC_CHANNEL_1

#define DEFAULT_RESOLUTION 16
#define DEFAULT_FREQUENCY  50

#define PIN_NOT_ATTACHED -1

class L293D {
  public:
    L293D();
    L293D(int8_t _pinIn1, int8_t _pinIn2, int8_t _pinIn3, int8_t _pinIn4, int8_t _pinEn1, int8_t _pinEn2);
    ~L293D();

    void AttachPinsMotor1(int8_t _pinIn1, int8_t _pinIn2, int8_t _pinEn1);
    void AttachPinsMotor2(int8_t _pinIn3, int8_t _pinIn4, int8_t _pinEn2);

    void Speed(int8_t _motor, int _value);
    void Forward(int8_t _motor, int _value = -1);
    void Backwards(int8_t _motor, int _value = -1); 
    void Stop(int8_t _motor);
    void Braking(int8_t _motor, int _value = -1);

    void SetPWM1(int8_t _channel1, int _frequency1, int _resolution1);
    void SetPWM2(int8_t _channel2, int _frequency2, int _resolution2);

    int speed1 = 0;
    int speed2 = 0;

  protected:
    
    int8_t pinIn1;
    int8_t pinIn2;
    int8_t pinIn3;
    int8_t pinIn4;

    int8_t pinEn1;
    int8_t pinEn2;

    int resolution1;
    int frequency1;
    int8_t channel1;

    int resolution2;
    int frequency2;
    int8_t channel2;

    int maxDuty1;
    int maxDuty2;
};


#endif
