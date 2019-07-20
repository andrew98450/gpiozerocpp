#include <LED.hpp>
#include <pigpio.h>
LED::LED(int pin,int init_value,bool pull_up)
{
    this->pin = pin;
    this->init_value = init_value;
    this->pull_up = pull_up;
    if(this->pull_up == true)
    {
        gpioSetPullUpDown(this->pin,PI_PUD_UP);
    }
    else
    {
        gpioSetPullUpDown(this->pin,PI_PUD_DOWN);
    }
    gpioSetMode(this->pin,PI_OUTPUT);
    gpioWrite(this->pin,this->init_value);
}
void LED::blink(double time,int n)
{
    if(pull_up==true)
    {
        if(n!=0)
        {
            while(n>0)
            {
                gpioWrite(pin,1);
                time_sleep(time);
                gpioWrite(pin,0);
                time_sleep(time);
                n--;
            }
        }
        else
        {
            while(true)
            {
                gpioWrite(pin,1);
                time_sleep(time);
                gpioWrite(pin,0);
                time_sleep(time);
            }
        }
    }
    else
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
}
int LED::getValue()
{
    return gpioRead(pin);
}
void LED::on()
{
    if(pull_up==true)
    {
        gpioWrite(pin,0);
    }
    else
    {
        gpioWrite(pin,1);
    }
}
void LED::off()
{
    if(pull_up==true)
    {
        gpioWrite(pin,1);
    }
    else
    {
        gpioWrite(pin,0);
    }
}
