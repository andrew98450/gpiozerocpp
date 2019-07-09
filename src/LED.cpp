#include <LED.hpp>
#include <pigpio.h>
LED::LED(int pin,int init_value)
{
    this->pin = pin;
    this->init_value = init_value;
    gpioSetMode(this->pin,PI_OUTPUT);
    gpioWrite(this->pin,this->init_value);
}
void LED::blink(double time,int n)
{
    if(n!=0)
    {
        while(n>0)
        {
            gpioWrite(pin,0);
            time_sleep(time);
            gpioWrite(pin,1);
            time_sleep(time);
            n--;
        }
    }
    else
    {
        while(true)
        {
            gpioWrite(pin,0);
            time_sleep(time);
            gpioWrite(pin,1);
            time_sleep(time);
        }
    }
}
int LED::getValue()
{
    return gpioRead(pin);
}
void LED::on()
{
    gpioWrite(pin,1);
}
void LED::off()
{
    gpioWrite(pin,0);
}
