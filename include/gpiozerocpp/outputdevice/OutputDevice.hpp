#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H
class OutputDevice
{
    private:
        int pin = 0;
        bool pull_up;
    public:
        OutputDevice(int pin,bool pull_up = true);
        void on();
        void off();
        int getValue();
};

#endif // OUTPUTDEVICE_H
