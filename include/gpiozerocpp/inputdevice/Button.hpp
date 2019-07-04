#ifndef BUTTON_H
#define BUTTON_H
#include <pigpio.h>
class Button
{
    protected:
        int pin = 0;
    public:
        Button(int pin)
        {
            this->pin = pin;
            gpioSetPullUpDown(this->pin,PI_PUD_UP);
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
        void wait_for_press(double timeout)
        {
            while(gpioRead(pin) != 0){ time_sleep(timeout); }
        }
        void wait_for_release(double timeout)
        {
            while(gpioRead(pin) != 1){ time_sleep(timeout); }
        }
};

#endif // BUTTON_H
