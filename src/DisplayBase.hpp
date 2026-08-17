#pragma once

#include "Arduino.h"
#include "PowerLink.cpp"



  
class DisplayBase
{
    protected:
    bool isMuted = false;
    unsigned int Laut = 0;
    
  
    
    
   
    void  PrintInfo(int val);
    void virtual PrintInfo(char* left,char * main,char * right);
    void virtual PrintInfo(int left,char * main,char * right= 0);
    void virtual PrintInfo(int left,char * main, int right= 0);
    void virtual PrintInfo(char* left,char * main,int right= 0);
    char* PrintDevice(int dev);
    void virtual SetSound(String bin,unsigned int type, unsigned int subtype, unsigned int value);
    
  public:

    void  PrintMute() ;

    void virtual PrintInfo(char * out)=0;
    void virtual Setup()= 0;
    void  PrintAudio(unsigned devId,unsigned int type, unsigned int seek, unsigned val );
    void  SetSound_Org(String bin,unsigned int type, unsigned int subtype, unsigned int value);
    
    void Print(PowerLink pl);
   
};
