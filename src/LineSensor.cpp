#include <LineSensor.hpp>
#include <pigpio.h>
LineSensor::LineSensor(int pin)
{
    this->pin = pin;
    gpioSetMode(this->pin,PI_INPUT);
}
int LineSensor::getValue()
{
    return gpioRead(pin);
}
void LineSensor::wait_for_line(double time)
{
    while(gpioRead(pin) != 0){ time_sleep(time); }
}
void LineSensor::wait_for_no_line(double time)
{
    while(gpioRead(pin) != 1){ time_sleep(time); }
}
