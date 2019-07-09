#include <RGBLED.hpp>
#include <pigpio.h>
#include <iostream>
#include <sstream>
RGBLED::RGBLED(int pin_r,int pin_g,int pin_b,int init_value[],bool pull_up)
{
    this->pin_r = pin_r;
    this->pin_g = pin_g;
    this->pin_b = pin_b;
    for(int i=0;i<3;i++)
    {
        this->init_value[i] = init_value[i];
    }
    this->pull_up = pull_up;
    this->pin_all[0] = this->pin_r;
    this->pin_all[1] = this->pin_g;
    this->pin_all[2] = this->pin_b;
    gpioSetMode(this->pin_r,PI_OUTPUT);
    gpioSetMode(this->pin_g,PI_OUTPUT);
    gpioSetMode(this->pin_b,PI_OUTPUT);
    if(pull_up == true)
    {
        gpioSetPullUpDown(this->pin_r,PI_PUD_UP);
        gpioSetPullUpDown(this->pin_g,PI_PUD_UP);
        gpioSetPullUpDown(this->pin_b,PI_PUD_UP);
    }
    else
    {
        gpioSetPullUpDown(this->pin_r,PI_PUD_DOWN);
        gpioSetPullUpDown(this->pin_g,PI_PUD_DOWN);
        gpioSetPullUpDown(this->pin_b,PI_PUD_DOWN);
    }
    for(int i=0;i<3;i++)
    {
        gpioWrite(this->pin_all[i],this->init_value[i]);
    }
}
void RGBLED::blink(double time,int r,int g,int b,int n)
{
    if(n!=0)
    {
        while(n>0)
        {
            gpioWrite(pin_r,r);
            gpioWrite(pin_g,g);
            gpioWrite(pin_b,b);
            time_sleep(time);
            if(pull_up == true)
            {
                gpioWrite(pin_r,1);
                gpioWrite(pin_g,1);
                gpioWrite(pin_b,1);
            }
            else
            {
                gpioWrite(pin_r,0);
                gpioWrite(pin_g,0);
                gpioWrite(pin_b,0);
            }
            time_sleep(time);
            n--;
        }
    }
    else
    {
        while(true)
        {
            gpioWrite(pin_r,r);
            gpioWrite(pin_g,g);
            gpioWrite(pin_b,b);
            time_sleep(time);
            if(pull_up == true)
            {
                gpioWrite(pin_r,1);
                gpioWrite(pin_g,1);
                gpioWrite(pin_b,1);
            }
            else
            {
                gpioWrite(pin_r,0);
                gpioWrite(pin_g,0);
                gpioWrite(pin_b,0);
            }
            time_sleep(time);
        }
    }
}
void RGBLED::on()
{
    if(pull_up ==true)
    {
        gpioWrite(pin_r,0);
        gpioWrite(pin_g,0);
        gpioWrite(pin_b,0);
    }
    else
    {
        gpioWrite(pin_r,1);
        gpioWrite(pin_g,1);
        gpioWrite(pin_b,1);
    }
}
void RGBLED::off()
{
    if(pull_up ==true)
    {
        gpioWrite(pin_r,1);
        gpioWrite(pin_g,1);
        gpioWrite(pin_b,1);
    }
    else
    {
        gpioWrite(pin_r,0);
        gpioWrite(pin_g,0);
        gpioWrite(pin_b,0);
    }
}
void RGBLED::getValue()
{
    for(int i=0;i<3;i++)
    {
        int tmp = gpioRead(pin_all[i]);
        std::stringstream ss;
        ss << tmp;
        std::cout << ss.str() << " ";
    }
    std::cout << std::endl;
}
void RGBLED::setValue(int r,int g,int b)
{
    gpioWrite(pin_r,r);
    gpioWrite(pin_g,g);
    gpioWrite(pin_b,b);
}
