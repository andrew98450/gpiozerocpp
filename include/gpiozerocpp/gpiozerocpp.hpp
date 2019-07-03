#ifndef GPIOZEROCPP_H
#define GPIOZEROCPP_H
#include <pigpio.h>
class gpiozerocpp{
    public:
        struct PIN
        {
            const int pin_2_SDA = 2;
            const int pin_3_SCL = 3;
            const int pin_4 = 4;
            const int pin_17 = 17;
            const int pin_27 = 27;
            const int pin_22 = 22;
            const int pin_10_MOSI = 10;
            const int pin_9_MISO = 9;
            const int pin_11_CLK = 11;
            const int pin_0_SDA = 0;
            const int pin_5 = 5;
            const int pin_6 = 6;
            const int pin_13 = 13;
            const int pin_19 = 19;
            const int pin_26 = 26;
            const int pin_14_TxD = 14;
            const int pin_15_RxD = 15;
            const int pin_18 = 18;
            const int pin_23 = 23;
            const int pin_24 = 24;
            const int pin_25 = 25;
            const int pin_8_CE0 = 8;
            const int pin_7_CE1 = 7;
            const int pin_1_SCL = 1;
            const int pin_12 = 12;
            const int pin_16 = 16;
            const int pin_20 = 20;
            const int pin_21 = 21;
            int gpio_all[17] = {pin_12,pin_16,pin_17,pin_18,
                            pin_19,pin_20,pin_21,pin_6,
                            pin_22,pin_23,pin_24,pin_25,
                            pin_26,pin_27,pin_4,pin_5,pin_13};
        };
        void init_pin()
        {
            gpioInitialise();
        }
        void clean_pin()
        {
            PIN pin;
            for(int i = 0;i < 17;i++)
            {
                gpioWrite(pin.gpio_all[i],0);
                gpioSetMode(pin.gpio_all[i],PI_INPUT);
            }
        }
};
#endif // GPIOZEROCPP_H
