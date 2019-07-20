#include <LCD.hpp>
#include <pigpio.h>
#include <string>
LCD::LCD(int bus,int addr,int flags,int width,bool backlight_on,int RS,int RW,int E,int BL,int B4)
{
    this->bus = bus;
    this->addr = addr;
    this->flags = flags;
    this->width = width;
    this->backlight_on = backlight_on;
    this->RS = (1<<RS);
    this->RW = RW;
    this->E = (1<<E);
    this->BL = (1<<BL);
    this->B4 = B4;
    this->hand = i2cOpen(this->bus,this->addr,this->flags);
    init();
}
void LCD::init()
{
    inst(0x33);
    inst(0x32);
    inst(0x06);
    inst(0x0C);
    inst(0x28);
    inst(0x01);
}
void LCD::byte(int MSb,int LSb)
{
    if(backlight_on == true)
    {
        MSb |= BL;
        LSb |= BL;
    }
    char data[4] = {MSb | E, MSb & ~E, LSb | E, LSb & ~E};
    i2cWriteDevice(hand,data,4);
}
void LCD::inst(int bits)
{
    int MSN = (bits>>4) & 0x0F;
    int LSN = bits & 0x0F;

    int MSb = MSN << B4;
    int LSb = LSN << B4;

    byte(MSb, LSb);
}
void LCD::data(int bits)
{
    int MSN = (bits>>4) & 0x0F;
    int LSN = bits & 0x0F;

    int MSb = (MSN << B4) | RS;
    int LSb = (LSN << B4) | RS;

    byte(MSb, LSb);
}
void LCD::move_to(int row,int col)
{
    inst(lcd_row[row]+col);
}
void LCD::put_chr(char ch)
{
    int ord = (int)ch;
    data(ord);
}
void LCD::put_str(int row,string text)
{
    for(int i=0;i<text.size();i++)
    {
        put_chr(text[i]);
    }
}
void LCD::put_line(int row,string text)
{
    for(int i=0;i<width-text.size();i++)
    {
        text += " ";
    }
    move_to(row,0);
    put_str(row,text);
}
void LCD::backlight(bool backs)
{
    this->backlight_on = backs;
}
void LCD::clear()
{
    move_to(0,0);
    inst(0x01);
}
void LCD::put_text(string text,int line)
{
    put_line(line,text);
}
void LCD::clear_text()
{
    clear();
}
void LCD::setbacklight(bool b)
{
    backlight(b);
}
