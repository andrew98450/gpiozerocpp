#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H
class DistanceSensor
{
    private:
        int echo_pin = 0;
        int trigger_pin = 0;
        double threshold_distance;
    public:
        DistanceSensor(int echo_pin,int trigger_pin,double threshold_distance = 0.1);
        double distance();
        void wait_for_in_range(double time);
        void wait_for_out_of_range(double time);
};

#endif // DISTANCESENSOR_H
