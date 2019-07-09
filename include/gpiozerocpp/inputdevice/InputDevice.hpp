#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H
class InputDevice
{
    private:
        int pin = 0;
        bool pull_up;
    public:
        InputDevice(int pin,bool pull_up = true);
        bool is_active();
        int getValue();
};

#endif // INPUTDEVICE_H
