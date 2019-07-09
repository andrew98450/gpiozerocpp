#include <TouchSensor.hpp>
#include <pigpio.h>
TouchSensor::TouchSensor(int pin,int pin2,int pin3,int pin4)
{
    this->pin = pin;
    this->pin2 = pin2;
    this->pin3 = pin3;
    this->pin4 = pin4;
    gpioSetMode(this->pin,PI_INPUT);
    gpioSetMode(this->pin2,PI_INPUT);
    gpioSetMode(this->pin3,PI_INPUT);
    gpioSetMode(this->pin4,PI_INPUT);
}
int TouchSensor::is_touch_button()
{
    int bt = 0;
    if(gpioRead(pin) == 1)
    {
        bt = 1;
    }
    else if(gpioRead(pin2) == 1)
    {
        bt = 2;
    }
    else if(gpioRead(pin3) == 1)
    {
        bt = 3;
    }
    else if(gpioRead(pin4) == 1)
    {
        bt = 4;
    }
    return bt;
}
int TouchSensor::getButton1Value()
{
    return gpioRead(pin);
}
int TouchSensor::getButton2Value()
{
    return gpioRead(pin2);
}
int TouchSensor::getButton3Value()
{
    return gpioRead(pin3);
}
int TouchSensor::getButton4Value()
{
    return gpioRead(pin4);
}
