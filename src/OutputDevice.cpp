#include <OutputDevice.hpp>
#include <pigpio.h>
OutputDevice::OutputDevice(int pin,bool pull_up)
{
    this->pin = pin;
    this->pull_up = pull_up;
    if(this->pull_up == true)
    {
        gpioSetPullUpDown(this->pin,PI_PUD_UP);
    }
    else
    {
        gpioSetPullUpDown(this->pin,PI_PUD_DOWN);
    }
    gpioSetMode(this->pin,PI_OUTPUT);
}
void OutputDevice::on()
{
    if(pull_up == true)
    {
        gpioWrite(pin,0);
    }
    else
    {
        gpioWrite(pin,1);
    }
}
void OutputDevice::off()
{
    if(pull_up == true)
    {
        gpioWrite(pin,1);
    }
    else
    {
        gpioWrite(pin,0);
    }
}
int OutputDevice::getValue()
{
    return gpioRead(pin);
}
