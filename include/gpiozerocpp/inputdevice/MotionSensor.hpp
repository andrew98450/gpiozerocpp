#ifndef MOTIONSENSOR_H
#define MOTIONSENSOR_H
#include <pigpio.h>
class MotionSensor
{
    protected:
        int pin = 0;
    public:
        MotionSensor(int pin)
        {
            this->pin = pin;
            gpioSetPullUpDown(this->pin,PI_PUD_DOWN);
            gpioSetMode(this->pin,PI_INPUT);
        }
        bool motion_detected()
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
        void wait_for_motion(double timeout)
        {
            while(motion_detected() != true) { time_sleep(timeout); }
        }
        void wait_for_no_motion(double timeout)
        {
            while(motion_detected() != false) { time_sleep(timeout); }
        }
};

#endif // MOTIONSENSOR_H
