#ifndef LED_H
#define LED_H
#include <pigpio.h>
#include <unistd.h>
using namespace std;
class LED
{
    protected:
        int pin = 0;
    public:
        LED(int pin)
        {
           this->pin = pin;
           gpioSetMode(this->pin,PI_OUTPUT);
        }
        void blink(int timeout,int n)
        {
            if(n!=0)
            {
                while(n>0)
                {
                    gpioWrite(pin,0);
                    gpioDelay(timeout);
                    gpioWrite(pin,1);
                    gpioDelay(timeout);
                    n--;
                }
            }
            else
            {
                while(true)
                {
                    gpioWrite(pin,0);
                    gpioDelay(timeout);
                    gpioWrite(pin,1);
                    gpioDelay(timeout);
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
};

#endif // LED_H
