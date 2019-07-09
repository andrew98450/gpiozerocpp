#ifndef LED_H
#define LED_H
class LED
{
    private:
        int pin = 0;
        int init_value = 0;
    public:
        LED(int pin,int init_value = 0);
        void blink(double time,int n);
        int getValue();
        void on();
        void off();
};

#endif // LED_H
