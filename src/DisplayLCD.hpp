
#include "DisplayBase.hpp"

#include "LiquidCrystal_PCF8574.h"
#include "Wire.h"

  

class DisplayLCD : public DisplayBase
{
    LiquidCrystal_PCF8574 lcd = LiquidCrystal_PCF8574(0x3f); 
    void virtual PrintInfo(char * out);
    
public: 
    void virtual Setup();
    DisplayLCD(){};
};
