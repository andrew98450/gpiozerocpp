#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H
class OutputDevice
{
    private:
        int pin = 0;
    public:
        OutputDevice(int pin);
        void on();
        void off();
        int getValue();
};

#endif // OUTPUTDEVICE_H
