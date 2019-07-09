#include <Relay.hpp>
#include <pigpio.h>
Relay::Relay(int pin)
{
    this->pin = pin;
    gpioSetMode(this->pin,PI_OUTPUT);
}
void Relay::poweron()
{
    gpioWrite(pin,0);
}
void Relay::poweroff()
{
    gpioWrite(pin,1);
}
int Relay::getValue()
{
    return gpioRead(pin);
}
