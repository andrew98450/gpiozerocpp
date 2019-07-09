#ifndef RELAY_H
#define RELAY_H
class Relay
{
    private:
        int pin = 0;
    public:
        Relay(int pin);
        void poweron();
        void poweroff();
        int getValue();
};

#endif // RELAY_H
