#ifndef PWMLED_H
#define PWMLED_H
#include <pigpio.h>
using namespace std;
class PWMLED
{
    protected:
        int pin = 0;
        int value = 100;
    public:
        PWMLED(int pin)
        {
            this->pin = pin;
            gpioSetMode(this->pin,PI_OUTPUT);
            gpioSetPWMrange(this->pin,100);
        }
        void blink(double timeout ,int n)
        {
            if(n!=0)
            {
                while(n>0)
                {
                    for(int i=0;i<=100;i++)
                    {
                        gpioPWM(pin,i);
                        time_sleep(timeout);
                    }
                    for(int i=100;i>=0;i--)
                    {
                        gpioPWM(pin,i);
                        time_sleep(timeout);
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
                        time_sleep(timeout);
                    }
                    for(int i=100;i>=0;i--)
                    {
                        gpioPWM(pin,i);
                        time_sleep(timeout);
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
        void setValue(int value)
        {
            this->value = value;
        }
        int getValue()
        {
            return value;
        }
        void on()
        {
            gpioPWM(pin,value);
        }
        void off()
        {
            gpioPWM(pin,0);
        }

};

#endif // PWMLED_H
