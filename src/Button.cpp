#include <Button.hpp>
#include <pigpio.h>
Button::Button(int pin)
{
    this->pin = pin;
    gpioSetPullUpDown(this->pin,PI_PUD_UP);
    gpioSetMode(this->pin,PI_INPUT);
}
bool Button::is_pressed()
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
void Button::wait_for_press(double time)
{
    while(gpioRead(pin) != 0){ time_sleep(time); }
}
void Button::wait_for_release(double time)
{
    while(gpioRead(pin) != 1){ time_sleep(time); }
}
