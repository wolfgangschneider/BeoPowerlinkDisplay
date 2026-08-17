
#include "DisplayBase.hpp"

#include "M5Core2.h"

class DisplayM5Core2 : public DisplayBase
{
   
  
    void virtual PrintInfo(char * out);
    void virtual PrintInfo(char* left,char * main,char * right);
    void virtual PrintInfo(int left,char * main,char * right= 0);
    void virtual PrintInfo(int left,char * main, int right= 0);
    void virtual PrintInfo(char* left,char * main,int right= 0);
  
   
  
public: 
    void virtual Setup();
    DisplayM5Core2(){};
  
};