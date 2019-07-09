#include <AngularServo.hpp>
#include <pigpio.h>
AngularServo::AngularServo(int pin,int init_value,int frequency,int max_range)
{
    this->pin = pin;
    this->init_value = init_value;
    this->frequency = frequency;
    this->max_range = max_range;
    gpioSetMode(this->pin,PI_OUTPUT);
    gpioPWM(this->pin,0);
    gpioSetPWMfrequency(this->pin, this->frequency);
    gpioSetPWMrange(this->pin, this->max_range);
}
void AngularServo::setAngle(int angle)
{
    gpioWrite(pin,1);
    gpioPWM(pin,angle);
    time_sleep(0.5);
    gpioWrite(pin,0);
}
void AngularServo::min()
{
    gpioWrite(pin,1);
    gpioPWM(pin,500);
    time_sleep(0.5);
    gpioWrite(pin,0);
}
void AngularServo::mid()
{
    gpioWrite(pin,1);
    gpioPWM(pin,1500);
    time_sleep(0.5);
    gpioWrite(pin,0);
}
void AngularServo::max()
{
    gpioWrite(pin,1);
    gpioPWM(pin,2400);
    time_sleep(0.5);
    gpioWrite(pin,0);
}
