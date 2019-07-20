#ifndef LCD_H
#define LCD_H
#include <string>
using namespace std;
class LCD
{
    private:
        int bus = 1;
        int addr = 0x27;
        int flags = 0;
        int width = 16;
        bool backlight_on = true;
        int RS=0;
        int RW=1;
        int E=2;
        int BL=3;
        int B4=4;
        int hand = 0;
    protected:
        int lcd_row[4] = {0x80, 0xC0, 0x94, 0xD4};
        void init();
        void backlight(bool backs);
        void byte(int MSb,int LSb);
        void inst(int bits);
        void data(int bits);
        void move_to(int row,int col);
        void put_chr(char ch);
        void put_str(int row,string text);
        void put_line(int row,string text);
        void clear();
    public:
        LCD(int bus=1,int addr=0x27,int flags=0,int width = 16,bool backlight_on=true,int RS=0,int RW=1,int E=2,int BL=3,int B4=4);
        void put_text(string text,int line);
        void clear_text();
        void setbacklight(bool b);
};

#endif // LCD_H
