#ifndef PWMLED_H
#define PWMLED_H
class PWMLED
{
    private:
        int pin = 0;
        int init_value = 0;
    public:
        PWMLED(int pin,int init_value = 0);
        void blink(double time,int n);
        void pwmValue(int value);
        int getValue();
        void on();
        void off();
};

#endif // PWMLED_H
