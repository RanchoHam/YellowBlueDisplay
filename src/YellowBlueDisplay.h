#ifndef YellowBlueDisplay_h
#define YellowBlueDisplay_h
#pragma once

#include <Arduino.h>
#include <string>
#include <vector>
#include <SSD1306Wire.h> // legacy include: `#include "SSD1306.h"`
//using namespace std;

class cYellowBlueDisplay : public SSD1306Wire {
public:
    // Parameterized Constructor
    //using SSD1306Wire::SSD1306Wire;
    cYellowBlueDisplay(uint8_t address, 
        int sda = -1, int scl = -1, 
        OLEDDISPLAY_GEOMETRY g = GEOMETRY_128_64, 
        HW_I2C i2cBus = I2C_ONE, 
        long  frequency = 700000
    ) ;

    void init(void);
    void clsBufferBlue(void);
    void setTitleYellow(char* strArg);
    void setTitleYellow(const char* strArg) {setTitleYellow((char*) strArg)};
    void printlnToBufferBlue(char* strArg);
    void printlnToBufferBlue(const char* strArg) {printlnToBufferBlue((char*) strArg)};
    void showDisplay(void);
    uint8_t  getMaxBufferDepth();
    uint8_t  setMaxBufferDepth(uint8_t depth);

private:
    int  _mySDA;
    int  _mySCL;
    uint8_t  _max_buffer_depth = 10;
    std::vector<std::string> _stringVectorBuffer;
    std::vector<std::string> _stringTitleBuffer;
    uint8_t  _LastTitleDepth = 0;
    uint8_t  _LastVectorDepth = 0;
};


#endif