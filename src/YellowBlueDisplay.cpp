// HW364A_Diplay class
//  Encapsulated all of the display I/O and definitions
//

#include <YellowBlueDisplay.h>

// Parameterized Constructor
cYellowBlueDisplay :: cYellowBlueDisplay(uint8_t address, 
    int SDA , int SCL,
    OLEDDISPLAY_GEOMETRY g, 
    HW_I2C i2cBus, 
    long  frequency) : SSD1306Wire::SSD1306Wire(address, SDA, SCL, g, i2cBus, frequency) {
    _mySDA = SDA;
    _mySCL = SCL;
    _stringTitleBuffer.clear();
    _stringVectorBuffer.clear();
}

void cYellowBlueDisplay :: init(void) {
    this->SSD1306Wire::init();
    this->flipScreenVertically();
    this->setContrast(255);
}

void cYellowBlueDisplay :: clsBufferBlue(void) {
    _stringVectorBuffer.clear();
    _LastBufferLength = 0;
}

void cYellowBlueDisplay :: printlnToBufferBlue(char* strArg) {
    if (_stringVectorBuffer.size()+1 > _max_buffer_depth ) {
      _stringVectorBuffer.erase(_stringVectorBuffer.begin());
    }
    _stringVectorBuffer.push_back(strArg);
}

void cYellowBlueDisplay :: setTitleYellow(char* strArg){
    _stringTitleBuffer.clear();
    _stringTitleBuffer.push_back(strArg);
    _LastTitleDepth = 0;
}

uint8_t cYellowBlueDisplay :: getMaxBufferDepth() {
    return _max_buffer_depth;
}

uint8_t cYellowBlueDisplay :: setMaxBufferDepth(uint8_t depth) {
    return _max_buffer_depth = (depth > 128) ? 128 : depth;
}

void cYellowBlueDisplay :: showDisplay(void) {
  uint8_t sVsize = _stringVectorBuffer.size();
  uint8_t sTsize = _stringTitleBuffer.size();
  if((sVsize > _LastVectorDepth) || (sTsize > _LastTitleDepth)){
    this->clear();
    int j=0;
    for (uint8_t i = 0; i < (3*(sVsize/3) + (sVsize%3)); i++) {
      if ((i+(j-1)) < sVsize) {
        j=0;
        auto it_begin = _stringVectorBuffer.begin(); 
        auto it_end = _stringVectorBuffer.end() ;     
        for (auto it = it_begin + i; (it != it_end) && (j < 3); ++it) {
          if (j++==0) {
            this->cls();
            // Print title line
            this->println(_stringTitleBuffer[0].c_str());
          }
          this->println(it->c_str());
        };
      };
      delay(1000);
    }
    _LastTitleDepth = _stringTitleBuffer.size();
    _LastVectorDepth = _stringVectorBuffer.size();
  }
}
    