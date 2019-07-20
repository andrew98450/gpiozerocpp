#include <RFIDSensor.hpp>
#include <pigpio.h>
#include <vector>
#include <string>
#include <sstream>
RFIDSensor::RFIDSensor(int RST_pin,int spi_ch,int band,int spi_flag)
{
    this->spi_ch = spi_ch;
    this->band = band;
    this->spi_flag = spi_flag;
    this->RST_pin = RST_pin;
    gpioSetMode(this->RST_pin,PI_OUTPUT);
    gpioWrite(this->RST_pin,1);
    MFRC522_Init();
}
void RFIDSensor::MFRC522_Reset()
{
    Write_MFRC522(CommandReg,PCD_RESETPHASE);
}
void RFIDSensor::Write_MFRC522(char addr,char val)
{
    hand = spiOpen(spi_ch,band,spi_flag);
    char sendData[2] = {(addr << 1) & 0x7E,val};
    spiWrite(hand,sendData,2);
    Close_MFRC522();
}
char RFIDSensor::Read_MFRC522(char addr)
{
    hand = spiOpen(spi_ch,band,spi_flag);
    char sendData[2] = {((addr << 1) & 0x7E) | 0x80,0};
    char recvData[2];
    spiXfer(hand,sendData,recvData,2);
    Close_MFRC522();
    return recvData[1];
}
void RFIDSensor::Close_MFRC522()
{
    spiClose(hand);
}
void RFIDSensor::SetBitMask(char reg,char mask)
{
    char tmp = Read_MFRC522(reg);
    Write_MFRC522(reg, tmp | mask);
}
void RFIDSensor::ClearBitMask(char reg,char mask)
{
    char tmp = Read_MFRC522(reg);
    Write_MFRC522(reg, tmp & (~mask));
}
void RFIDSensor::AntennaOn()
{
    char temp = Read_MFRC522(TxControlReg);
    if ((temp & 0x03)!=0x03)
    {
        SetBitMask(TxControlReg, 0x03);
    }
}
void RFIDSensor::AntennaOff()
{
    ClearBitMask(TxControlReg, 0x03);
}
RFIDSensor::Arges RFIDSensor::MFRC522_ToCard(char command,vector<char> sendData)
{
    Arges arg;
    vector<char> backData;
    int backLen = 0;
    int status = MI_ERR;
    char irqEn = 0x00;
    char waitIRq = 0x00;
    int lastBits = 0;
    int n = 0;
    if (command == PCD_AUTHENT)
    {
        irqEn = 0x12;
        waitIRq = 0x10;
    }
    if (command == PCD_TRANSCEIVE)
    {
        irqEn = 0x77;
        waitIRq = 0x30;
    }
    Write_MFRC522(CommIEnReg, irqEn | 0x80);
    ClearBitMask(CommIrqReg, 0x80);
    SetBitMask(FIFOLevelReg, 0x80);

    Write_MFRC522(CommandReg, PCD_IDLE);

    for(int i = 0;i<sendData.size();i++)
    {
        Write_MFRC522(FIFODataReg, sendData[i]);
    }

    Write_MFRC522(CommandReg, command);

    if (command == PCD_TRANSCEIVE)
    {
        SetBitMask(BitFramingReg, 0x80);
    }
    int i = 2000;
    while (true)
    {
        n = Read_MFRC522(CommIrqReg);
        i -= 1;
        if (!((i != 0) && !(n & 0x01) && !(n & waitIRq)))
        {
            break;
        }
    }

    ClearBitMask(BitFramingReg, 0x80);

    if (i != 0)
    {
        if ((Read_MFRC522(ErrorReg) & 0x1B)==0x00)
        {
            status = MI_OK;
            if (n & irqEn & 0x01)
            {
                status = MI_NOTAGERR;
            }
            if (command == PCD_TRANSCEIVE)
            {
                n = Read_MFRC522(FIFOLevelReg);
                lastBits = Read_MFRC522(ControlReg) & 0x07;
                if (lastBits != 0)
                {
                    backLen = (n - 1) * 8 + lastBits;
                }
                else
                {
                    backLen = n * 8;
                }
                if (n == 0)
                {
                    n = 1;
                }
                if (n > MAX_LEN)
                {
                    n = MAX_LEN;
                }
                for (int i=0;i<n;i++)
                {
                    backData.push_back(Read_MFRC522(FIFODataReg));
                }
            }
        }
    }
    else
    {
        status = MI_ERR;
    }
    arg.status = status;
    arg.backData = backData;
    arg.backLen = backLen;
    return arg;
}
RFIDSensor::Arges RFIDSensor::MFRC522_Request(char regMode)
{
    Arges args,reads;
    vector<char> TagType;

    Write_MFRC522(BitFramingReg, 0x07);

    TagType.push_back(regMode);
    reads = MFRC522_ToCard(PCD_TRANSCEIVE, TagType);
    if ((reads.status != MI_OK) || (reads.backLen != 16))
    {
        reads.status = MI_ERR;
    }
    args.status = reads.status;
    args.backLen = reads.backLen;
    return args;
}
RFIDSensor::Arges RFIDSensor::MFRC522_Anticoll()
{
    Arges args,reads;
    int serNumCheck = 0;
    vector<char> serNum;

    Write_MFRC522(BitFramingReg, 0x00);

    serNum.push_back(PICC_ANTICOLL);
    serNum.push_back(0x20);

    reads = MFRC522_ToCard(PCD_TRANSCEIVE, serNum);
    if (reads.status == MI_OK)
    {
        if (reads.backData.size() == 5)
        {
            for(int i = 0;i<4;i++)
            {
                serNumCheck = serNumCheck ^ (int)reads.backData[i];
            }
            if (serNumCheck != (int)reads.backData[4])
            {
                reads.status = MI_ERR;
            }
        }
        else
        {
            reads.status = MI_ERR;
        }
    }
    args.status = reads.status;
    args.backData = reads.backData;
    return args;
}
vector<char> RFIDSensor::CalulateCRC(vector<char> pIndata)
{
    ClearBitMask(DivIrqReg, 0x04);
    SetBitMask(FIFOLevelReg, 0x80);

    for(int i=0;i<pIndata.size();i++)
    {
        Write_MFRC522(FIFODataReg, pIndata[i]);
    }

    Write_MFRC522(CommandReg, PCD_CALCCRC);
    int i = 0xFF;
    while(true)
    {
        char n = Read_MFRC522(DivIrqReg);
        i -= 1;
        if (!((i != 0) && !(n & 0x04)))
        {
            break;
        }
    }
    vector<char> pOutData;
    pOutData.push_back(Read_MFRC522(CRCResultRegL));
    pOutData.push_back(Read_MFRC522(CRCResultRegM));
    return pOutData;
}
char RFIDSensor::MFRC522_SelectTag(vector<char> serNum)
{
    Arges args,reads;
    vector<char> buf;
    buf.push_back(PICC_SElECTTAG);
    buf.push_back(0x70);

    for(int i=0;i<5;i++)
    {
        buf.push_back(serNum[i]);
    }
    vector<char> pOut = CalulateCRC(buf);
    buf.push_back(pOut[0]);
    buf.push_back(pOut[1]);
    reads = MFRC522_ToCard(PCD_TRANSCEIVE, buf);
    if ((reads.status == MI_OK) && (reads.backLen == 0x18))
    {
        return reads.backData[0];
    }
    else
    {
        return 0;
    }
}
char RFIDSensor::MFRC522_Auth(char authMode,int blockAddr,vector<char> SectorKey,vector<char> serNum)
{
    Arges args,reads;
    vector<char> buff;
    buff.push_back(authMode);
    buff.push_back(blockAddr);
    for(int i=0;i<SectorKey.size();i++)
    {
        buff.push_back(SectorKey[i]);
    }
    for(int i=0;i<4;i++)
    {
        buff.push_back(serNum[i]);
    }

    reads = MFRC522_ToCard(PCD_AUTHENT, buff);
    args.status = reads.status;
    return args.status;
}
void RFIDSensor::MFRC522_StopCrypto1()
{
    ClearBitMask(Status2Reg, 0x08);
}
string RFIDSensor::MFRC522_Read(int blockAddr)
{
    Arges reads;
    string result = "";
    vector<char> recvData;
    recvData.push_back(PICC_READ);
    recvData.push_back(blockAddr);
    vector<char> pOut = CalulateCRC(recvData);
    recvData.push_back(pOut[0]);
    recvData.push_back(pOut[1]);
    reads = MFRC522_ToCard(PCD_TRANSCEIVE, recvData);
    if (!(reads.status == MI_OK))
    {
        result = "";
    }
    if (reads.backData.size() == 16)
    {
        stringstream stream;
        stream << blockAddr;
        result = "Sector " + stream.str() + "\r\n";
        for(int i=0;i<reads.backData.size();i++)
        {
            stringstream backs;
            backs << (int)reads.backData[i];
            result += backs.str() + " ";
        }
        result += "\r\n";
    }
    else
    {
        result = "";
    }
    return result;
}
string RFIDSensor::MFRC522_ReadText(int blockAddr)
{
    Arges reads;
    string result = "";
    vector<char> recvData;
    recvData.push_back(PICC_READ);
    recvData.push_back(blockAddr);
    vector<char> pOut = CalulateCRC(recvData);
    recvData.push_back(pOut[0]);
    recvData.push_back(pOut[1]);
    reads = MFRC522_ToCard(PCD_TRANSCEIVE, recvData);
    if (!(reads.status == MI_OK))
    {
        result = "";
    }
    if (reads.backData.size() == 16)
    {
        stringstream stream;
        stream << blockAddr;
        result = "Sector " + stream.str() + "\r\n";
        for(int i=0;i<reads.backData.size();i++)
        {
            stringstream backs;
            backs << reads.backData[i];
            result += backs.str();
        }
        result += "\r\n";
    }
    else
    {
        result = "";
    }
    return result;
}
bool RFIDSensor::MFRC522_Write(int blockAddr,char* writeData)
{
    Arges reads;
    vector<char> buff;
    buff.push_back(PICC_WRITE);
    buff.push_back(blockAddr);
    vector<char> crc = CalulateCRC(buff);
    buff.push_back(crc[0]);
    buff.push_back(crc[1]);
    reads = MFRC522_ToCard(PCD_TRANSCEIVE, buff);
    if (!(reads.status == MI_OK) || !(reads.backLen == 4) || !((reads.backData[0] & 0x0F) == 0x0A))
    {
        reads.status = MI_ERR;
    }
    if (reads.status == MI_OK)
    {
        vector<char> buf;
        for (int i=0;i<16;i++)
        {
            buf.push_back(writeData[i]);
        }
        vector<char> crc = CalulateCRC(buf);
        buf.push_back(crc[0]);
        buf.push_back(crc[1]);
        reads = MFRC522_ToCard(PCD_TRANSCEIVE, buf);
        if (!(reads.status == MI_OK) || !(reads.backLen == 4) || !((reads.backData[0] & 0x0F) == 0x0A))
        {
            return false;
        }
        if (reads.status == MI_OK)
        {
            return true;
        }
    }
}
 string RFIDSensor::MFRC522_DumpClassic1K(char authMode,vector<char> key,vector<char> uid)
 {
    string result = "";
    int status = 0;
    for (int i = 0;i<64;i++)
    {
        status = MFRC522_Auth(authMode, i, key, uid);
        if(status == MI_OK)
        {
            result += MFRC522_Read(i);
        }
        else
        {
            result += "Reading Error\r\n";
        }
    }
    return result;
 }
 void RFIDSensor::MFRC522_Init()
 {
    MFRC522_Reset();

    Write_MFRC522(TModeReg, 0x8D);
    Write_MFRC522(TPrescalerReg, 0x3E);
    Write_MFRC522(TReloadRegL, 30);
    Write_MFRC522(TReloadRegH, 0);

    Write_MFRC522(TxAutoReg, 0x40);
    Write_MFRC522(ModeReg, 0x3D);
    AntennaOn();
 }
bool RFIDSensor::rfid_detected()
{
    Arges req;
    req = MFRC522_Request(PICC_REQIDL);
    if(req.status == MI_OK)
    {
        return true;
    }
    else
    {
        return false;
    }
}
vector<char> RFIDSensor::getuid()
{
    Arges args;
    args = MFRC522_Anticoll();
    vector<char> uid;
    if(args.status == MI_OK)
    {
        uid = args.backData;
    }
    return uid;
}
void RFIDSensor::key_to_vector(char* raw_key,vector<char> &key)
{
    key.clear();
    for(int i=0;i<6;i++)
    {
        key.push_back(raw_key[i]);
    }
}
string RFIDSensor::Read(char authMode,int block,vector<char> key,vector<char> uid)
{
    string result = "";
    if(authMode == 'A')
    {
        int status = MFRC522_Auth(PICC_AUTHENT1A,block,key,uid);
        if(status == MI_OK)
        {
            result += MFRC522_Read(block);
        }
    }
    else
    {
        int status = MFRC522_Auth(PICC_AUTHENT1B,block,key,uid);
        if(status == MI_OK)
        {
            result += MFRC522_Read(block);
        }
    }
    return result;
}
string RFIDSensor::Read_Text(char authMode,int block,vector<char> key,vector<char> uid)
{
    string result = "";
    if(authMode == 'A')
    {
        int status = MFRC522_Auth(PICC_AUTHENT1A,block,key,uid);
        if(status == MI_OK)
        {
            result += MFRC522_ReadText(block);
        }
    }
    else
    {
        int status = MFRC522_Auth(PICC_AUTHENT1B,block,key,uid);
        if(status == MI_OK)
        {
            result += MFRC522_ReadText(block);
        }
    }
    return result;
}
string RFIDSensor::Dump(char authMode,vector<char> key,vector<char> uid)
{
    string result = "";
    if(authMode == 'A')
    {
        result = MFRC522_DumpClassic1K(PICC_AUTHENT1A,key,uid);
    }
    else
    {
        result = MFRC522_DumpClassic1K(PICC_AUTHENT1B,key,uid);
    }
    return result;
};
bool RFIDSensor::Write(char authMode,int block,char* writeData,vector<char> key,vector<char> uid)
{
    bool result = false;
    if(authMode == 'A')
    {
        int status = MFRC522_Auth(PICC_AUTHENT1A,block,key,uid);
        if(status == MI_OK)
        {
            result = MFRC522_Write(block,writeData);
        }
    }
    else
    {
        int status = MFRC522_Auth(PICC_AUTHENT1B,block,key,uid);
        if(status == MI_OK)
        {
            result = MFRC522_Write(block,writeData);
        }
    }
    return result;
}
void RFIDSensor::Clear(char authMode,int block,vector<char> key,vector<char> uid)
{
    char data[16];
    if(authMode == 'A')
    {
        int status = MFRC522_Auth(PICC_AUTHENT1B,block,key,uid);
        if(status == MI_OK)
        {
            for(int i=0;i<16;i++)
            {
                data[i] = 0x00;
            }
            MFRC522_Write(block,data);
        }
    }
    else
    {
        int status = MFRC522_Auth(PICC_AUTHENT1B,block,key,uid);
        if(status == MI_OK)
        {
            for(int i=0;i<16;i++)
            {
                data[i] = 0x00;
            }
            MFRC522_Write(block,data);
        }
    }
}
void RFIDSensor::Tag(vector<char> uid)
{
    MFRC522_SelectTag(uid);
}
void RFIDSensor::Stop()
{
    MFRC522_StopCrypto1();
}
int RFIDSensor::uid_to_num(vector<char> uid)
{
    int n = 0;
    for(int i=0;i<5;i++)
    {
        n = n * 256 + (int)uid[i];
    }
    return n;
}
