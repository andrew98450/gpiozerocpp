#ifndef ANGULARSERVO_H
#define ANGULARSERVO_H
class AngularServo
{
    private:
        int pin = 0;
        int init_value = 0;
        int frequency = 400;
        int max_range = 2500;
    public:
        AngularServo(int pin,int init_value = 0,int frequency = 400,int max_range = 2500);
        void setAngle(int angle);
        void min();
        void mid();
        void max();
};

#endif // ANGULARSERVO_H
