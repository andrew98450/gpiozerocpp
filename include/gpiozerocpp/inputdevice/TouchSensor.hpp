#ifndef TOUCHSENSOR_H
#define TOUCHSENSOR_H

class TouchSensor
{
    private:
        int pin = 0,pin2 = 0,pin3 = 0,pin4 = 0;
    public:
        TouchSensor(int pin,int pin2,int pin3,int pin4);
        int is_touch_button();
        int getButton1Value();
        int getButton2Value();
        int getButton3Value();
        int getButton4Value();
};

#endif // TOUCHSENSOR_H
