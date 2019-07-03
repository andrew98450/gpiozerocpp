# gpiozerocpp
gpiozero C/C++ Library

This Library is Preview Version

Welcome to try and offer advice.

Example:

#include <gpiozerocpp/gpiozerocpp.hpp>

#include <gpiozerocpp/outputdevice/PWMLED.hpp>

int main()

{

    gpiozerocpp gpio;
		
    gpiozerocpp::PIN pin;
		
    gpio.init_pin();
		
    PWMLED pwm(pin.pin_17);
		
    pwm.blink(5000,0);
		
}

