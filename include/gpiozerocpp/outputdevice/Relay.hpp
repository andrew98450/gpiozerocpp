#ifndef RELAY_H
#define RELAY_H
#include <pigpio.h>
class Relay
{
    protected:
        int pin = 0;
    public:
        Relay(int pin)
        {
            this->pin = pin;
            gpioSetMode(this->pin,PI_OUTPUT);
        }
        void poweron()
        {
            gpioWrite(pin,0);
        }
        void poweroff()
        {
            gpioWrite(pin,1);
        }
        int getValue()
        {
            return gpioRead(pin);
        }
};

#endif // RELAY_H
