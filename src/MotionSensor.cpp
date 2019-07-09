#include <MotionSensor.hpp>
#include <pigpio.h>
MotionSensor::MotionSensor(int pin)
{
    this->pin = pin;
    gpioSetPullUpDown(this->pin,PI_PUD_DOWN);
    gpioSetMode(this->pin,PI_INPUT);
}
bool MotionSensor::motion_detected()
{
    if(gpioRead(pin) == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void MotionSensor::wait_for_motion(double time)
{
    while(motion_detected() != true) { time_sleep(time); }
}
void MotionSensor::wait_for_no_motion(double time)
{
    while(motion_detected() != false) { time_sleep(time); }
}
