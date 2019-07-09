#include <gpiozerocpp/gpiozerocpp.hpp>
#include <pigpio.h>
void gpiozerocpp::setup_pin()
{
    gpioInitialise();
}
void gpiozerocpp::clean_pin()
{
    gpiozerocpp::PIN pin;
    for(int i = 0;i < 17;i++)
    {
        gpioWrite(pin.gpio_all[i],0);
        gpioSetMode(pin.gpio_all[i],PI_INPUT);
    }
}


