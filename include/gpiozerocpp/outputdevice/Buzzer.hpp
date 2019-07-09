#ifndef BUZZER_H
#define BUZZER_H
class Buzzer
{
    private:
        int pin = 0;
    public:
        Buzzer(int pin);
        void beep(double on_time=0.5,double off_time=0.5,int n=0);
        void on();
        void off();
        int getValue();
};

#endif // BUZZER_H
