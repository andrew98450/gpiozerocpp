#ifndef PWMLED_H
#define PWMLED_H
#include <pigpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
class PWMLED
{
    protected:
        int pin = 0;
    public:
        PWMLED(int pin)
        {
            this->pin = pin;
            gpioSetMode(this->pin,PI_OUTPUT);
            gpioSetPWMrange(this->pin,100);
        }
        void blink(int time,int n)
        {
            if(n!=0)
            {
                while(n>0)
                {
                    for(int i=0;i<=100;i++)
                    {
                        gpioPWM(pin,i);
                        gpioDelay(time);
                    }
                    for(int i=100;i>=0;i--)
                    {
                        gpioPWM(pin,i);
                        gpioDelay(time);
                    }
                    n--;
                }
            }
            else
            {
                while(true)
                {
                    for(int i=0;i<=100;i++)
                    {
                        gpioPWM(pin,i);
                        gpioDelay(time);
                    }
                    for(int i=100;i>=0;i--)
                    {
                        gpioPWM(pin,i);
                        gpioDelay(time);
                    }
                }
            }

        }
        void pwmValue(int value)
        {
            if(value >= 0 && value <= 100)
            {
                gpioPWM(pin,value);
            }
        }
        void on()
        {
            gpioPWM(pin,100);
        }
        void off()
        {
            gpioPWM(pin,0);
        }

};

#endif // PWMLED_H
