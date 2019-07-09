#ifndef SERVO_H
#define SERVO_H
class Servo
{
    private:
        int pin = 0;
        int init_value = 0;
    public:
        Servo(int pin,int init_value = 0);
        void min();
        void mid();
        void max();
};

#endif // SERVO_H
