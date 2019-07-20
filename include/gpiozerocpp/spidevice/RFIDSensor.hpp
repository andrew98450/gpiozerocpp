#ifndef RFIDSENSOR_H
#define RFIDSENSOR_H

#include <vector>
#include <string>
using namespace std;
class RFIDSensor
{
    private:
        int spi_ch = 0;
        int band = 1000000;
        int spi_flag = 0;
        int RST_pin = 25;
        int hand = 0;
        int status = 0;
        int MAX_LEN = 16;
    protected:
        char PCD_IDLE = 0x00;
        char PCD_AUTHENT = 0x0E;
        char PCD_RECEIVE = 0x08;
        char PCD_TRANSMIT = 0x04;
        char PCD_TRANSCEIVE = 0x0C;
        char PCD_RESETPHASE = 0x0F;
        char PCD_CALCCRC = 0x03;

        char PICC_REQIDL = 0x26;
        char PICC_REQALL = 0x52;
        char PICC_ANTICOLL = 0x93;
        char PICC_SElECTTAG = 0x93;
        char PICC_AUTHENT1A = 0x60;
        char PICC_AUTHENT1B = 0x61;
        char PICC_READ = 0x30;
        char PICC_WRITE = 0xA0;
        char PICC_DECREMENT = 0xC0;
        char PICC_INCREMENT = 0xC1;
        char PICC_RESTORE = 0xC2;
        char PICC_TRANSFER = 0xB0;
        char PICC_HALT = 0x50;

        int MI_OK = 0;
        int MI_NOTAGERR = 1;
        int MI_ERR = 2;

        char Reserved00 = 0x00;
        char CommandReg = 0x01;
        char CommIEnReg = 0x02;
        char DivlEnReg = 0x03;
        char CommIrqReg = 0x04;
        char DivIrqReg = 0x05;
        char ErrorReg = 0x06;
        char Status1Reg = 0x07;
        char Status2Reg = 0x08;
        char FIFODataReg = 0x09;
        char FIFOLevelReg = 0x0A;
        char WaterLevelReg = 0x0B;
        char ControlReg = 0x0C;
        char BitFramingReg  = 0x0D;
        char CollReg = 0x0E;
        char Reserved01 = 0x0F;

        char Reserved10 = 0x10;
        char ModeReg = 0x11;
        char TxModeReg = 0x12;
        char RxModeReg = 0x13;
        char TxControlReg = 0x14;
        char TxAutoReg = 0x15;
        char TxSelReg = 0x16;
        char RxSelReg = 0x17;
        char RxThresholdReg = 0x18;
        char DemodReg = 0x19;
        char Reserved11 = 0x1A;
        char Reserved12 = 0x1B;
        char MifareReg = 0x1C;
        char Reserved13 = 0x1D;
        char Reserved14 = 0x1E;
        char SerialSpeedReg = 0x1F;

        char Reserved20 = 0x20;
        char CRCResultRegM = 0x21;
        char CRCResultRegL = 0x22;
        char Reserved21 = 0x23;
        char ModWidthReg = 0x24;
        char Reserved22 = 0x25;
        char RFCfgReg = 0x26;
        char GsNReg = 0x27;
        char CWGsPReg = 0x28;
        char ModGsPReg = 0x29;
        char TModeReg = 0x2A;
        char TPrescalerReg = 0x2B;
        char TReloadRegH = 0x2C;
        char TReloadRegL = 0x2D;
        char TCounterValueRegH = 0x2E;
        char TCounterValueRegL = 0x2F;

        char Reserved30 = 0x30;
        char TestSel1Reg = 0x31;
        char TestSel2Reg = 0x32;
        char TestPinEnReg = 0x33;
        char TestPinValueReg = 0x34;
        char TestBusReg = 0x35;
        char AutoTestReg = 0x36;
        char VersionReg = 0x37;
        char AnalogTestReg = 0x38;
        char TestDAC1Reg = 0x39;
        char TestDAC2Reg = 0x3A;
        char TestADCReg = 0x3B;
        char Reserved31 = 0x3C;
        char Reserved32 = 0x3D;
        char Reserved33 = 0x3E;
        char Reserved34 = 0x3F;
        struct Arges
        {
            int status;
            vector<char> backData;
            int backLen;
        };
        void MFRC522_Reset();
        void Write_MFRC522(char addr,char val);
        char Read_MFRC522(char addr);
        void Close_MFRC522();
        void SetBitMask(char reg,char mask);
        void ClearBitMask(char reg,char mask);
        void AntennaOn();
        void AntennaOff();
        Arges MFRC522_ToCard(char command,vector<char> sendData);
        Arges MFRC522_Request(char regMode);
        Arges MFRC522_Anticoll();
        vector<char> CalulateCRC(vector<char> pIndata);
        char MFRC522_SelectTag(vector<char> serNum);
        char MFRC522_Auth(char authMode,int blockAddr,vector<char> SectorKey,vector<char> serNum);
        void MFRC522_StopCrypto1();
        string MFRC522_Read(int blockAddr);
        string MFRC522_ReadText(int blockAddr);
        bool MFRC522_Write(int blockAddr,char* writeData);
        string MFRC522_DumpClassic1K(char authMode,vector<char> key,vector<char> uid);
        void MFRC522_Init();
    public:
        RFIDSensor(int RST_pin = 25,int spi_ch = 0,int band = 1000000,int spi_flag = 0);
        bool rfid_detected();
        vector<char> getuid();
        void key_to_vector(char* raw_key,vector<char> &key);
        int uid_to_num(vector<char> uid);
        string Read(char authMode,int block,vector<char> key,vector<char> uid);
        string Read_Text(char authMode,int block,vector<char> key,vector<char> uid);
        bool Write(char authMode,int block,char* writeData,vector<char> key,vector<char> uid);
        string Dump(char authMode,vector<char> key,vector<char> uid);
        void Clear(char authMode,int block,vector<char> key,vector<char> uid);
        void Tag(vector<char> uid);
        void Stop();
};

#endif // RFIDSENSOR_H
