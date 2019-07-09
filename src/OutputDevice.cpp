#include <OutputDevice.hpp>
#include <pigpio.h>
OutputDevice::OutputDevice(int pin)
{
    this->pin = pin;
    gpioSetMode(this->pin,PI_OUTPUT);
}
void OutputDevice::on()
{
    gpioWrite(pin,1);
}
void OutputDevice::off()
{
    gpioWrite(pin,0);
}
int OutputDevice::getValue()
{
    return gpioRead(pin);
}
