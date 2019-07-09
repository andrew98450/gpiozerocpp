#include <InputDevice.hpp>
#include <pigpio.h>
InputDevice::InputDevice(int pin,bool pull_up)
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
    gpioSetMode(this->pin,PI_INPUT);
}
bool InputDevice::is_active()
{
    bool result;
    if(pull_up == true)
    {
        if(gpioRead(pin) == 0)
        {
            result = true;
        }
        else
        {
            result = false;
        }
    }
    else
    {
        if(gpioRead(pin) == 1)
        {
            result = true;
        }
        else
        {
            result = false;
        }
    }
    return result;
}
int InputDevice::getValue()
{
    return gpioRead(pin);
}
