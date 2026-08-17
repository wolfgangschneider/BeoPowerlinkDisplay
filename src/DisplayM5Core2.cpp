

#include "DisplayM5Core2.hpp"


void DisplayM5Core2::Setup()
{
  
   M5.begin();
   M5.Lcd.fillScreen(BLACK);

   M5.Lcd.setCursor(15, 100); 
   M5.Lcd.setTextColor(WHITE); 
   M5.Lcd.setTextSize(3);  
   M5.Lcd.printf("B&O Powerlink M5");  

   
}



void DisplayM5Core2::PrintInfo(char * out)
{
   M5.Lcd.clear();
   M5.Lcd.setCursor(5, 100); 
   M5.Lcd.setTextColor(GREEN); 
   M5.Lcd.setTextSize(4);  
   M5.Lcd.printf(out); 
 
}

void DisplayM5Core2::PrintInfo(int left,char * main, int right)
{
    char output[50]; 
    //sprintf(output,"%-2d  %-10s%2d",left,main,right); 
    sprintf(output,"%-2d %-8s%2d",left,main,right); 
    PrintInfo(output);
}

void DisplayM5Core2::PrintInfo(char* left,char * main,char * right)
{ 
    char output[50]; 
    sprintf(output,"%-2s %-*s   %s",left,8,main,right); 
    PrintInfo(output);
    
}
void DisplayM5Core2::PrintInfo(int left,char * main,char * right)
{
    char output[50]; 
    sprintf(output,"%-2d %-8s %s",left,main,right); 
    PrintInfo(output);
    
}

void DisplayM5Core2::PrintInfo(char* left,char * main,int right)
{
    char output[50]; 
    sprintf(output,"%-2s %-8s %2d",left,main,right); 
    PrintInfo(output);
}
