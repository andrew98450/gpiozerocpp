#include <ADCSensor.hpp>
#include <pigpio.h>
ADCSensor::ADCSensor(int channel,int spi_ch,int band,int spi_flag)
{
    this->channel = channel;
    this->spi_ch = spi_ch;
    this->band = band;
    this->spi_flag = spi_flag;
}
double ADCSensor::value()
{
    double val = 0;
    if(channel >= 0 && channel < 8)
    {
        int h = spiOpen(0,1350000,0);
        char ch = (8+channel)<<4;
        char sendData[] = {1,ch,0};
        char recvData[3];
        spiXfer(h,sendData,recvData,3);
        val = ((recvData[1] << 8) | recvData[2]) & 0x3FF;
        spiClose(h);
    }
    else
    {
        val = -1;
    }
    return val;
}

