

#include "DisplayLCD.hpp"


void DisplayLCD::Setup()
{
    lcd.begin(20, 4); // initialize the lcd
    lcd.clear();
    lcd.setBacklight(255);

    lcd.home(); 
    lcd.print("B&O Powerlink LCD");  
}

void DisplayLCD::PrintInfo(char * out)
{
    lcd.home(); 
    lcd.clear();
    lcd.print(out); 
}

