#include <DistanceSensor.hpp>
#include <pigpio.h>
DistanceSensor::DistanceSensor(int echo_pin,int trigger_pin,double threshold_distance)
{
    this->echo_pin = echo_pin;
    this->trigger_pin = trigger_pin;
    this->threshold_distance = threshold_distance;
    gpioSetMode(this->trigger_pin,PI_OUTPUT);
    gpioSetMode(this->echo_pin,PI_INPUT);
    gpioSetPullUpDown(this->echo_pin,PI_PUD_DOWN);
}
double DistanceSensor::distance()
{
    double start_time;
    double end_time;
    double diff_time;
    gpioWrite(trigger_pin,0);
    time_sleep(0.05);
    gpioWrite(trigger_pin,1);
    time_sleep(0.05);
    gpioWrite(trigger_pin,0);
    while(gpioRead(echo_pin) == 0)
    {
        start_time = time_time();
    }
    while(gpioRead(echo_pin) == 1)
    {
        end_time = time_time();
    }
    diff_time = end_time - start_time;
    double distances = diff_time * 17150 * 0.01;
    return distances;
}
void DistanceSensor::wait_for_in_range(double time)
{
    while(distance() > threshold_distance){ time_sleep(time); }
}
void DistanceSensor::wait_for_out_of_range(double time)
{
    while(distance() < threshold_distance){ time_sleep(time); }
}

