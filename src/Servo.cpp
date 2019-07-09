#include <Servo.hpp>
#include <pigpio.h>
Servo::Servo(int pin,int init_value)
{
    this->pin = pin;
    this->init_value = init_value;
    gpioSetMode(this->pin,PI_OUTPUT);
    gpioPWM(this->pin,0);
    gpioSetPWMfrequency(this->pin, 400);
    gpioSetPWMrange(this->pin, 2500);
}
void Servo::min()
{
    gpioWrite(pin,1);
    gpioPWM(pin,500);
    time_sleep(0.5);
    gpioWrite(pin,0);
}
void Servo::mid()
{
    gpioWrite(pin,1);
    gpioPWM(pin,1500);
    time_sleep(0.5);
    gpioWrite(pin,0);
}
void Servo::max()
{
    gpioWrite(pin,1);
    gpioPWM(pin,2400);
    time_sleep(0.5);
    gpioWrite(pin,0);
}
