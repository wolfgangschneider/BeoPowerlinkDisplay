
//https://www.mikrocontroller.net/attachment/33137/datalink.pdf
#pragma once
#include "Arduino.h"

#define BODev_Radio  193
#define BODev_CD     210
#define BODev_Phone  211
#define BODev_Tape   209
#define BODev_ATP2   212
#define BODev_Aux     13
#define BODev_TV     192
#define BODev_PC     203

#define BODev_CDV    198
#define BODev_VTape  197
#define BODev_VSAt   202
#define BODev_AAUX   195
#define BODev_VAUX   194
#define BODev_AUX    215

#define BODev_VTP2   200


typedef struct
 {
     unsigned int Device;
     unsigned int ValueType;
     // Byte4: 0 = normal track/channel select, 16 = cueing forward (>>),
     // 32 = cueing backward (<<) - verified against real CD captures
     unsigned int Seek;
     unsigned int Value;
 } BOAudo;

 typedef struct 
 {
     unsigned int Type;
     unsigned int SubType;
     unsigned int Value;    
 } BOSound;
 
class PowerLink
{
    unsigned int readBinaryString(String s)
    {
      // Serial.println(s);
      int result = 0;

      for(int i =0;i< s.length();i++)
      {
        result <<= 1;
        if(s[i] == '1') result |= 1;
      }
      return result;
    }

    // Command=59: SelectSource/Audio - Device/ValueType/Value at fixed byte boundaries
    void decodeAudio()
    {
        Audio.Device    = Byte2;
        Audio.ValueType = Byte3;
        Audio.Seek      = Byte4;
        Audio.Value     = Byte5;
    }

    // Command=51: Sound. SubType consistently sits at [19,27) regardless of
    // Type - verified against real Bass/Treble (type 72) and Loudness
    // (type 78, subtype 132) captures. Value's general position [35,43) is
    // only a fallback; known subtypes override it with their own verified
    // narrower field.
    void decodeSound()
    {
        Sound.Type    = Byte2;
        Sound.SubType = readBinaryString(Data.substring(19, 27));
        Sound.Value   = readBinaryString(Data.substring(35, 43));

        if(Sound.Type == 78 &&  Sound.SubType == 132) // Laudn: 0=off, 8=on
          Sound.Value = readBinaryString(Data.substring(43, 47));
        else if(Sound.Type == 72 && (Sound.SubType == 130 || Sound.SubType == 131)) // Bass/Treble
          Sound.Value = readBinaryString(Data.substring(27, 35));

        Serial.printf("  Sound: Type=%u SubType=%u Value=%u\n", Sound.Type, Sound.SubType, Sound.Value);
    }

    public:
        String Data;
        unsigned int Byte1 =0;
        unsigned int Byte2 =0;
        unsigned int Byte3 =0;
        unsigned int Byte4 =0;
        unsigned int Byte5 =0;

        BOAudo Audio;
        BOSound Sound;
        unsigned int Command=0;

        // parses raw bits (as read from PLBusReader::poll) into Byte1..5,
        // then dispatches by Command into Audio/Sound
        explicit PowerLink(const String &bits)
        {
            Data = bits;
            Serial.printf("frame: %u bits  %s\n", Data.length(), Data.c_str());

            Byte1 = readBinaryString(Data.substring(0, 8));
            Byte2 = readBinaryString(Data.substring(8, 16));
            Byte3 = readBinaryString(Data.substring(16, 24));
            Byte4 = readBinaryString(Data.substring(24, 32));
            Byte5 = readBinaryString(Data.substring(32, 40));
            Command = Byte1;

            if(Command == 59) decodeAudio();
            else if(Command == 51) decodeSound();
        }

         void writeHIGH(int ms)
        {
            digitalWrite(25, HIGH);
            delayMicroseconds(ms);
            digitalWrite(25, LOW);
            delayMicroseconds(200);
            
        }


  
        void write(String bin)
        {
            int t1=3125;
            int t2=6250;
            int t3=9375;
            int t4=12500;
            int t5=15625;
        
           
          
            int previousValue = -1; // No previous value initially
            writeHIGH(t5);
            Serial.println(bin.length());
            
            for(int i =0;i< bin.length();i++)
            {
                char c = bin[i];
                if (c == '0') 
                {
                    if (previousValue == 0) 
                    {
                        writeHIGH(t2);
                    } 
                    else if (previousValue == 1) 
                    {
                        writeHIGH(t1);
                    }
                    previousValue = 0;
                } 
                else if (c == '1') 
                {
                    if (previousValue == 0) 
                    {
                        writeHIGH(t3);
                    } 
                    else if (previousValue == 1) 
                    {
                        writeHIGH(t2);
                    }
                    previousValue = 1;
                }
                //writeHIGH(previousValue == 0 ? t2 : t3); // Write the new bit's timing
            }

            writeHIGH(t4);
           
        }

};
