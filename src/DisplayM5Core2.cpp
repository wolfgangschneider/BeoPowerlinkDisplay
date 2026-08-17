

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
   // at textSize(4) the screen fits ~13 characters before wrapping - cut
   // off anything longer instead of letting it wrap onto a second line
   const int maxChars = 13;
   char truncated[maxChars + 1];
   strncpy(truncated, out, maxChars);
   truncated[maxChars] = '\0';

   M5.Lcd.clear();
   M5.Lcd.setCursor(5, 100);
   M5.Lcd.setTextColor(GREEN);
   M5.Lcd.setTextSize(4);
   M5.Lcd.printf("%s", truncated);

}

// name field is 6 wide - the longest real device name ("A-TAPE"/"V-TAPE")
// is exactly 6 chars, so this stays tight without cutting any of them off
void DisplayM5Core2::PrintInfo(int left,char * main, int right)
{
    char output[50];
    sprintf(output,"%-2d %-6.6s %2d",left,main,right);
    PrintInfo(output);
}

void DisplayM5Core2::PrintInfo(char* left,char * main,char * right)
{
    char output[50];
    sprintf(output,"%-2s %-6.6s %s",left,main,right);
    PrintInfo(output);

}
void DisplayM5Core2::PrintInfo(int left,char * main,char * right)
{
    char output[50];
    sprintf(output,"%-2d %-6.6s %s",left,main,right);
    PrintInfo(output);

}

void DisplayM5Core2::PrintInfo(char* left,char * main,int right)
{
    char output[50];
    sprintf(output,"%-2s %-6.6s %2d",left,main,right);
    PrintInfo(output);
}
