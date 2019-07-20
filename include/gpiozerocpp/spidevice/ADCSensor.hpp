#ifndef ADCSENSOR_H
#define ADCSENSOR_H
class ADCSensor
{
    private:
        int channel = 0;
        int spi_ch = 0;
        int band = 1350000;
        int spi_flag = 0;
    public:
        ADCSensor(int channel = 0,int spi_ch = 0,int band = 1350000,int spi_flag = 0);
        double value();
};

#endif // ADCSENSOR_H
