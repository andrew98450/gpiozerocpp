#ifndef MOTIONSENSOR_H
#define MOTIONSENSOR_H
class MotionSensor
{
    private:
        int pin = 0;
    public:
        MotionSensor(int pin);
        bool motion_detected();
        void wait_for_motion(double time);
        void wait_for_no_motion(double time);
};

#endif // MOTIONSENSOR_H
