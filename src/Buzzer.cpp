#include <Buzzer.hpp>
#include <pigpio.h>
Buzzer::Buzzer(int pin)
{
    this->pin = pin;
    gpioSetMode(this->pin,PI_OUTPUT);
}
void Buzzer::beep(double on_time,double off_time,int n)
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
void Buzzer::on()
{
    gpioWrite(pin,1);
}
void Buzzer::off()
{
    gpioWrite(pin,0);
}
int Buzzer::getValue()
{
    return gpioRead(pin);
}
