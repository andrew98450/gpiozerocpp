#include <gpiozerocpp/gpiozerocpp.hpp>
#include <pigpio.h>
void gpiozerocpp::setup_pin()
{
    gpioInitialise();
}
void gpiozerocpp::clean_pin()
{
    gpioTerminate();
}
void gpiozerocpp::sleep(double time)
{
    time_sleep(time);
}

