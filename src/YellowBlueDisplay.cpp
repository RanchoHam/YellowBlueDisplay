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
    _stringBufferTitle.clear();
    _stringVectorBuffer.clear();
}

void cYellowBlueDisplay :: init(void) {
    this->SSD1306Wire::init();
    this->flipScreenVertically();
    this->setContrast(255);
}

void cYellowBlueDisplay :: clsBufferBlue(void) {
    _stringVectorBuffer.clear();
}

void cYellowBlueDisplay :: printlnToBufferBlue(char* strArg) {
    if (_stringVectorBuffer.size()+1 > _max_buffer_depth ) {
      _stringVectorBuffer.erase(_stringVectorBuffer.begin());
    }
    _stringVectorBuffer.push_back(strArg);
}

void cYellowBlueDisplay :: setTitleYellow(char* strArg){
    _stringBufferTitle.clear();
    _stringBufferTitle.push_back(strArg);
}

uint8_t cYellowBlueDisplay :: getMaxBufferDepth() {
    return _max_buffer_depth;
}

uint8_t cYellowBlueDisplay :: setMaxBufferDepth(uint8_t depth) {
    return _max_buffer_depth = (depth > 128) ? 128 : depth;
}

void cYellowBlueDisplay :: showDisplay(void) {
  this->clear();
  uint8_t sVsize=_stringVectorBuffer.size();
  //Serial.printf("showDisplay\n");
  //Serial.printf("sVsize: %d\n", sVsize);
  //Serial.printf("sVsize/3: %d\n", sVsize/3);
  //Serial.printf("sVsize%%3: %d\n", sVsize%3);
  int j=0;
  for (uint8_t i = 0; i < (3*(sVsize/3) + (sVsize%3)); i++) {
    //Serial.printf("i+(j-1): %d, sVsize: %d\n", i+(j-1), sVsize);
    if ((i+(j-1)) < sVsize) {
      j=0;
      auto it_begin = _stringVectorBuffer.begin(); 
      auto it_end = _stringVectorBuffer.end() ;     
      for (auto it = it_begin + i; (it != it_end) && (j < 3); ++it) {
        if (j++==0) {
          this->cls(); //Serial.printf("cleared @ i = %d\n%s\n", i, _stringBufferTitle[0].c_str()); // delay(1000);
          // Print title line
          this->println(_stringBufferTitle[0].c_str());
        }
        this->println(it->c_str());
        //Serial.printf("i=%2d, j=%d, '%s'\n", i, j, it->c_str());
      };
    };
    delay(1000);
  }
}
    