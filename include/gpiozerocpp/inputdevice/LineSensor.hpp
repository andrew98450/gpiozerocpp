#ifndef LINESENSOR_H
#define LINESENSOR_H
class LineSensor
{
    private:
        int pin = 0;
    public:
        LineSensor(int pin);
        void wait_for_line(double time);
        void wait_for_no_line(double time);
        int getValue();
};

#endif // LINESENSOR_H
