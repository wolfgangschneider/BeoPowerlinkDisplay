
#include "Arduino.h"

#include "DisplayBase.hpp"
#include "PLBusReader.hpp"


#if defined(m5stackatom)
    #include "DisplayLCD.hpp"
 #elif defined(m5stackcore2)
    #include "DisplayM5Core2.hpp"
#endif

/*

Device
              device                              prog    Aud dev ??  C/V val
00S 00111011 11000001 01000000 00000000 00000011 Rad C3   059 193 064 000 003
00S 00111011 11000001 01001000 01101100 00100010 Rad L34  059 193 072 108 034
00S 00111011 11000001 01000000 00000000 00000100 Rad C4   059 193 064 000 004  
00S 00111011 11010010 01000000 00000000 00000001 CD1      059 210 064 000 001
00S 00111011 11010011 01001000 01101100 00100010 Phone    059 211 072 108 034
00S 00111011 11010001 01001000 01101100 00100010 A-Tape   059 209 072 108 034
00S 00111011 11010100 01000000 00000000 00000000 ATap2    059 212 064 000 000

Lautstärke
00S 00111011 11000001 01001000 01101000 00100000 Rad L32  059 193 072 108 032
00S 00111011 11000001 01001000 01101000 00100000 Rad L32  059 193 072 108 032
00S 00111011 11000001 01000000 00000000 00000100 Rad L32  059 193 064 000 004

 */



int mute =0;

#if defined(m5stackatom)
    PLBusReader reader(GPIO_NUM_26);
 #elif defined(m5stackcore2)
    PLBusReader reader(GPIO_NUM_32);
#endif

//new
DisplayBase* display;

 

void setup()
{

  #if defined(m5stackatom)
    display = new DisplayLCD();
   #elif defined(m5stackcore2)
    display = new DisplayM5Core2();
  #endif

   #if  defined(m5stackatom)
    Wire.begin(25,21);
    mute=33;
   #endif

   pinMode(mute, INPUT);

   display->Setup();
   reader.begin();
Serial.begin(115200);
   Serial.print("\nHello world.") ;

}
int counter;
void loop()
{
 // bool isMuted = digitalRead(mute)== false;
 // if(isMuted == true)
 // {
 // int i =0;
 //  display->PrintMute();
 // }
// else
//{
  // 1. read: block for the next raw frame off the bus
  String bits;
  if (!reader.poll(bits)) return;

  // 2. decode: parse it into Command/Audio/Sound
  PowerLink PL(bits);

 //PL.write("00110011010011101011001000001111000001010001000");
 //PL.write("001110111100000101100000000001000000000100000000");

  // 3. send to display
  display->Print(PL);

//}

}
