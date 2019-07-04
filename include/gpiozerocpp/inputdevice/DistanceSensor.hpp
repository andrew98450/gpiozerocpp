#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H
#include <pigpio.h>
using namespace std;
class DistanceSensor
{
    protected:
        int echo_pin = 0;
        int trigger_pin = 0;
        float threshold_distance = 10;
    public:
        DistanceSensor(int echo_pin,int trigger_pin,int threshold_distance = 10)
        {
            this->echo_pin = echo_pin;
            this->trigger_pin = trigger_pin;
            this->threshold_distance = threshold_distance;
            gpioSetMode(this->trigger_pin,PI_OUTPUT);
            gpioSetMode(this->echo_pin,PI_INPUT);
            gpioSetPullUpDown(this->echo_pin,PI_PUD_DOWN);
        }
        double distance()
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
            double distances = diff_time * 17150;
            return distances;
        }
        void wait_for_in_range(double timeout)
        {
            while(distance() > threshold_distance){ time_sleep(timeout); }
        }
        void wait_for_out_of_range(double timeout)
        {
            while(distance() < threshold_distance){ time_sleep(timeout); }
        }
};

#endif // DISTANCESENSOR_H
