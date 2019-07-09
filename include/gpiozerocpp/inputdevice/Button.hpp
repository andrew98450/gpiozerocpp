#ifndef BUTTON_H
#define BUTTON_H
class Button
{
    private:
        int pin = 0;
    public:
        Button(int pin);
        bool is_pressed();
        void wait_for_press(double time);
        void wait_for_release(double time);
};

#endif // BUTTON_H
