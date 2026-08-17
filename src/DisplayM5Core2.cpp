

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



// shared DisplayBase formatting (Bass/Treble/Volume/Laudn) pads fields
// wider than this screen has room for. If `in` is too long, shrink the
// longest run of interior spaces (the padding between fields) just
// enough to fit - leave the leading indent and the trailing value alone.
static void fitToWidth(const char *in, char *out, size_t maxLen)
{
    size_t len = strlen(in);
    if (len <= maxLen)
    {
        strcpy(out, in);
        return;
    }

    size_t bestStart = 0, bestLen = 0;
    size_t i = 1; // start at 1 so a leading run of spaces is never picked
    while (i < len)
    {
        if (in[i] == ' ')
        {
            size_t runStart = i;
            while (i < len && in[i] == ' ') i++;
            size_t runLen = i - runStart;
            if (runLen > bestLen)
            {
                bestLen = runLen;
                bestStart = runStart;
            }
        }
        else i++;
    }

    size_t toRemove = len - maxLen;
    if (toRemove > bestLen) toRemove = bestLen;

    memcpy(out, in, bestStart);
    strcpy(out + bestStart, in + bestStart + toRemove);

    // no interior padding to shrink (or not enough) - fall back to a
    // plain trailing cut so we still fit
    if (strlen(out) > maxLen) out[maxLen] = '\0';
}

void DisplayM5Core2::PrintInfo(char * out)
{
   // at textSize(4) the screen fits ~13 characters before wrapping
   const int maxChars = 13;
   char fitted[50];
   fitToWidth(out, fitted, maxChars);

   M5.Lcd.clear();
   M5.Lcd.setCursor(5, 100);
   M5.Lcd.setTextColor(GREEN);
   M5.Lcd.setTextSize(4);
   M5.Lcd.printf("%s", fitted);

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
