#ifndef BUZZER_H
#define BUZZER_H
#include <pigpio.h>
class Buzzer
{
    protected:
        int pin = 0;
    public:
        Buzzer(int pin)
        {
            this->pin = pin;
            gpioSetMode(this->pin,PI_OUTPUT);
        }
        void beep(double on_time=0.5,double off_time=0.5,int n=0)
        {
            if(n!=0)
            {
                while(n>0)
                {
                    gpioWrite(pin,1);
                    time_sleep(on_time);
                    gpioWrite(pin,0);
                    time_sleep(off_time);
                    n--;
                }
            }
            else
            {
                while(true)
                {
                    gpioWrite(pin,1);
                    time_sleep(on_time);
                    gpioWrite(pin,0);
                    time_sleep(off_time);
                }
            }
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

#endif // BUZZER_H
