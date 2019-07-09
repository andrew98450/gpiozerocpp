#ifndef RGBLED_H
#define RGBLED_H
class RGBLED
{
    private:
        int pin_r = 0;
        int pin_g = 0;
        int pin_b = 0;
        int init_value[3];
        bool pull_up;
        int pin_all[3];
    public:
        RGBLED(int pin_r,int pin_g,int pin_b,int init_value[],bool pull_up);
        void blink(double time,int r,int g,int b,int n);
        void on();
        void off();
        void getValue();
        void setValue(int r,int g,int b);
};

#endif // RGBLED_H
