#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H
#include <pigpio.h>
class OutputDevice
{
    protected:
        int pin = 0;
    public:
        OutputDevice(int pin)
        {
            this->pin = pin;
            gpioSetMode(this->pin,PI_OUTPUT);
        }
        void on()
        {
            gpioWrite(pin,1);
        }
        void off()
        {
            gpioWrite(pin,0);
        }
        int getValue()
        {
            return gpioRead(pin);
        }
};

#endif // OUTPUTDEVICE_H
