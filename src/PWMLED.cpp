#include <PWMLED.hpp>
#include <pigpio.h>
PWMLED::PWMLED(int pin,int init_value)
{
    this->pin = pin;
    this->init_value = init_value;
    gpioSetMode(this->pin,PI_OUTPUT);
    gpioSetPWMrange(this->pin,100);
    gpioWrite(this->pin,this->init_value);
}
void PWMLED::blink(double time,int n)
{
    if(n!=0)
    {
        while(n>0)
        {
            for(int i=0;i<=100;i++)
            {
                gpioPWM(pin,i);
                time_sleep(time);
            }
            for(int i=100;i>=0;i--)
            {
                gpioPWM(pin,i);
                time_sleep(time);
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
                time_sleep(time);
            }
            for(int i=100;i>=0;i--)
            {
                gpioPWM(pin,i);
                time_sleep(time);
            }
        }
    }
}
void PWMLED::pwmValue(int value)
{
    if(value >= 0 && value <= 100)
    {
        gpioPWM(pin,value);
    }
}
int PWMLED::getValue()
{
    return gpioGetPWMdutycycle(pin);
}
void PWMLED::on()
{
    gpioPWM(pin,100);
}
void PWMLED::off()
{
    gpioPWM(pin,0);
}
