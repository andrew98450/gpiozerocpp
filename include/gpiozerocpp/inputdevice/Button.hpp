#ifndef BUTTON_H
#define BUTTON_H
#include <pigpio.h>
class Button
{
    protected:
        int pin = 0;
    public:
        Button(int pin,bool pull_up)
        {
            this->pin = pin;
            if(pull_up == true)
            {
                gpioSetPullUpDown(this->pin,PI_PUD_UP);
            }
            else
            {
                gpioSetPullUpDown(this->pin,PI_PUD_DOWN);
            }
            gpioSetMode(this->pin,PI_INPUT);
        }
        bool is_pressed()
        {
            if(gpioRead(pin) == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        void wait_for_press(int timeout)
        {
            while(gpioRead(pin) != 0){ gpioDelay(timeout); }
        }
        void wait_for_release(int timeout)
        {
            while(gpioRead(pin) != 1){ gpioDelay(timeout); }
        }
};

#endif // BUTTON_H
