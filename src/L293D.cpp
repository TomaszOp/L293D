#include "L293D.h"

L293D::L293D(){
  this->pinIn1 = PIN_NOT_ATTACHED;
  this->pinIn2 = PIN_NOT_ATTACHED;
  this->pinEn1 = PIN_NOT_ATTACHED;
  this->pinIn3 = PIN_NOT_ATTACHED;
  this->pinIn4 = PIN_NOT_ATTACHED;
  this->pinEn2 = PIN_NOT_ATTACHED;

  this->resolution1 = DEFAULT_RESOLUTION;
  this->frequency1 = DEFAULT_FREQUENCY;
  this->channel1 = DEFAULT_CHANNEL1;

  this->resolution2 = DEFAULT_RESOLUTION;
  this->frequency2 = DEFAULT_FREQUENCY;
  this->channel2 = DEFAULT_CHANNEL2;

  this->maxDuty1 = pow(2, this->resolution1)-1;
  this->maxDuty2 = pow(2, this->resolution2)-1;
}

L293D::L293D(int8_t _pinIn1, int8_t _pinIn2, int8_t _pinIn3, int8_t _pinIn4, int8_t _pinEn1, int8_t _pinEn2) {
  AttachPinsMotor1(_pinIn1, _pinIn2, _pinEn1);
  AttachPinsMotor2(_pinIn3, _pinIn4, _pinEn2);
}

L293D::~L293D() {

  if(this->pinEn1 != PIN_NOT_ATTACHED)
    ledcDetach(this->pinEn1);

  if(this->pinEn2 != PIN_NOT_ATTACHED)
    ledcDetach(this->pinEn2);

  AttachPinsMotor1(PIN_NOT_ATTACHED, PIN_NOT_ATTACHED, PIN_NOT_ATTACHED);
  AttachPinsMotor2(PIN_NOT_ATTACHED, PIN_NOT_ATTACHED, PIN_NOT_ATTACHED);
}

void L293D::AttachPinsMotor1(int8_t _pinIn1, int8_t _pinIn2, int8_t _pinEn1)
{
  this->pinIn1 = _pinIn1;
  pinMode(this->pinIn1, OUTPUT);
  this->pinIn2 = _pinIn2;
  pinMode(this->pinIn2, OUTPUT);
  this->pinEn1 = _pinEn1;

  if(this->pinEn1 != PIN_NOT_ATTACHED)
  {
    pinMode(this->pinEn1, OUTPUT);
    ledcAttachChannel(this->pinEn1, this->frequency1, this->resolution1, this->channel1);
  }
}

void L293D::AttachPinsMotor2(int8_t _pinIn3, int8_t _pinIn4, int8_t _pinEn2)
{
  this->pinIn3 = _pinIn3;
  pinMode(this->pinIn3, OUTPUT);
  this->pinIn4 = _pinIn4;
  pinMode(this->pinIn4, OUTPUT);

  this->pinEn2 = _pinEn2;

  if(this->pinEn2 != PIN_NOT_ATTACHED)
  {
    pinMode(this->pinEn2, OUTPUT);
    ledcAttachChannel(this->pinEn2, this->frequency2, this->resolution2, this->channel2);
  }
}

/// @brief Set speed motor
/// @param _motor 1 (motor with pins 3,5) or 2 (motor with pins 11,14)
/// @param _value 
void L293D::Speed(int8_t _motor, int _value){
  if(_motor == 1)
  {
    int duty = map(_value, 0, 100, 0, this->maxDuty1);
    ledcWrite(this->pinEn1, duty);

    this->speed1 = _value;
  }
  else if(_motor == 2)
  {
    int duty = map(_value, 0, 100, 0, this->maxDuty2);
    ledcWrite(this->pinEn2, duty);

    this->speed2 = _value;
  }
}

void L293D::Forward(int8_t _motor, int _value){
  if(_motor == 1)
  {
    digitalWrite(this->pinIn1, HIGH);
    digitalWrite(this->pinIn2, LOW);
  }
  else if(_motor == 2)
  {
    digitalWrite(this->pinIn3, HIGH);
    digitalWrite(this->pinIn4, LOW);
  }

  if(_value != -1)
    Speed(_motor, _value);
}

void L293D::Backwards(int8_t _motor, int _value){
  if(_motor == 1)
  {
    digitalWrite(this->pinIn1, LOW);
    digitalWrite(this->pinIn2, HIGH);
  }
  else if(_motor == 2)
  {
    digitalWrite(this->pinIn3, LOW);
    digitalWrite(this->pinIn4, HIGH);
  }

  if(_value != -1)
    Speed(_motor, _value);
}

void L293D::Stop(int8_t _motor){
  if(_motor == 1)
  {
    digitalWrite(this->pinIn1, LOW);
    digitalWrite(this->pinIn2, LOW);
  }
  else if(_motor == 2)
  {
    digitalWrite(this->pinIn3, LOW);
    digitalWrite(this->pinIn4, LOW);
  }
}

void L293D::Braking(int8_t _motor, int _value){
  if(_motor == 1)
  {
    digitalWrite(this->pinIn1, HIGH);
    digitalWrite(this->pinIn2, HIGH);
  }
  else if(_motor == 2)
  {
    digitalWrite(this->pinIn3, HIGH);
    digitalWrite(this->pinIn4, HIGH);
  }

  if(_value != -1)
    Speed(_motor, _value);
}

void L293D::SetPWM1(int8_t _channel1, int _frequency1, int _resolution1){
  this->channel1 = _channel1;
  this->frequency1 = _frequency1;
  this->resolution1 = _resolution1;

  this->maxDuty2 = pow(2, this->resolution2)-1;
}

void L293D::SetPWM2(int8_t _channel2, int _frequency2, int _resolution2){
  this->channel2 = _channel2;
  this->frequency2 = _frequency2;
  this->resolution2 = _resolution2;

  this->maxDuty2 = pow(2, this->resolution2)-1;
}




