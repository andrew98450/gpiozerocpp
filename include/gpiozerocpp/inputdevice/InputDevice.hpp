#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H
#include <pigpio.h>
class InputDevice
{
    protected:
    int pin = 0;
    bool pull_up;
    public:
        InputDevice(int pin,bool pull_up = true)
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
        bool is_active()
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
        int getValue()
        {
            return gpioRead(pin);
        }
};

#endif // INPUTDEVICE_H
