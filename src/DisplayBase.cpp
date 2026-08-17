

#include "DisplayBase.hpp"


/*
DisplayBase::DisplayBase()
{
    //lcd = new LiquidCrystal_PCF8574(0x3f); 

}
*/
void DisplayBase::PrintMute()
{
     PrintInfo("__");
    //lcd.home(); 
    //lcd.print("__");  
}
 void DisplayBase::PrintAudio(unsigned devId,unsigned int type, unsigned int seek, unsigned val )
{
    static unsigned int chan =0;
    static unsigned int chanSeek =0;


    char* Device =PrintDevice(devId);



    if(type == 72) // channel
      Laut = val;
    else
    {
      chan =  val;
      chanSeek = seek;
    }

    char output[50];

    if(isMuted)
    {
      PrintInfo("__",Device,chan);
    }
    else if(devId == BODev_PC)
    {
         PrintInfo(Laut,Device,"");
    }
    else
    {
      if(chan ==0)
         PrintInfo(Laut,Device,"");
      else if(chanSeek == 16) // cueing forward
         PrintInfo(Laut,Device,">>");
      else if(chanSeek == 32) // cueing backward
         PrintInfo(Laut,Device,"<<");
      else if(chanSeek == 48) // pause (16|32)
         PrintInfo(Laut,Device,"<>");
      else
         PrintInfo(Laut,Device,chan);
    }

}

char* DisplayBase::PrintDevice(int dev)
{
  static char notfound[16];
  switch(dev)
  {
    case BODev_Radio:
      return "RADIO";
      break;
    case BODev_CD:
      return "CD";
      break;
    case BODev_Phone:
      return "PHONE";
      break;
    case BODev_Tape:
      return "A-TAPE";
      break;
    case BODev_ATP2:
      return "A-TP2";
      break;
    case BODev_Aux:
      return "Aux";
      break;
   case BODev_TV:
      return "TV";
      break;   
   case BODev_PC:
      return "PC";
      break;

 case BODev_CDV:
      return "CDV";
      break;
 case BODev_VTape:
      return "V-TAPE";
      break;
 case BODev_VSAt:
      return "V-SAT";
      break;
 case BODev_AAUX:
      return "A-AUX";
      break;
 case BODev_VAUX:
      return "V-AUX";
      break;
 case BODev_AUX:
      return "AUX";
      break;
 case BODev_VTP2:
      return "V-TP2";
      break;
 
    default:
       sprintf(notfound,"?%d?",dev); 
       return notfound;    
      break;
   
  }
}

void DisplayBase::SetSound(String bin,unsigned int type, unsigned int subtype, unsigned int value)
{
   // int laut = value;
    char output[50]; 
    
        if(subtype == 135) // VOLUME (sound)
        {
          //Laut = value;
          sprintf(output,"    %-8s  %2d","VOLUME" ,value ); 
          PrintInfo(output);
          return;
        }
        
        if(subtype == 132) // LAUDN
        {
          char* txt = "OFF";   
          if(value == 8)
            txt = "ON";
       
          sprintf(output,"    %-7s  %-s","LAUDN",txt ); 
          PrintInfo(output);
          return;
        }
   
        if(subtype == 144) // mute
        {
          PrintMute();
          return;
        }
        
        if(subtype == 128) // VOLUME Beolink active
        {
          Laut = value;
          PrintInfo(Laut);
          //lcd.home(); 
          //lcd.print(Laut);
          return; 
        }
        
        if(subtype==129) // Bal
        {
          char strBal[4] = "___";
          if(value <= 9 && value>0)
            strBal[2] = value +'0';
          else if(value > 246)
            strBal[0] = 256-value+'0';
            
          sprintf(output,"    %-9s%+3s","BAL" , strBal); 
          PrintInfo(output);
          return;
        }
     
    if(subtype == 130 || subtype == 131) // bass & Terrible
    {
        char* txt = "?";   
        if(subtype == 130)
          txt = "BASS";
        else if(subtype==131)  
          txt = "TREBLE";
        
        if(value ==0)
            sprintf(output,"    %-10s__",txt );
        else 
            sprintf(output,"    %-10s%+2d",txt , (char)value); 

        PrintInfo(output);
        return;
        
    }

       
    sprintf(output,"%11s% 4d","ST NotFound" , subtype); 
    PrintInfo(output);
  
    
}

void DisplayBase::SetSound_Org(String bin,unsigned int type, unsigned int subtype, unsigned int value)
{
   // int laut = value;
    char output[50]; 
    
    if(type == 78)// volume
    {
        if(subtype == 135) // VOLUME
        {
          //Laut = value;
          sprintf(output,"    %-8s  %2d","VOLUME" ,value ); 
        }
        else if(subtype == 132) // LAUDN
        {
          char* txt = "OFF";
          if(value == 8)
            txt = "ON";

          sprintf(output,"    %-7s  %-s","LAUDN",txt );

        }
        else
        {
           sprintf(output,"%11s% 4d","ST NotFound" , subtype);
        }
    }
    else if (type == 76) // BAL
    {
        if(subtype == 144) // mute
        {
          PrintMute();
          return;
        }
        else if(subtype == 128) // VOLUME
        {
          Laut = value;
          PrintInfo(Laut);
          //lcd.home(); 
          //lcd.print(Laut);
          return; 
        }
        else if(subtype==129)
        {
          char strBal[4] = "___";
          if(value <= 9 && value>0)
            strBal[2] = value +'0';
          else if(value > 246)
            strBal[0] = 256-value+'0';
            
          sprintf(output,"    %-9s%+3s","BAL" , strBal); 
        }
        else
        {
           sprintf(output,"%11s% 4d","ST NotFound" , subtype); 
        }
    }
    
    else if (type == 72) // BASS & TREBLE
    {
        char* txt = "?";   
        if(subtype == 130)
          txt = "BASS";
        else if(subtype==131)  
          txt = "TREBLE";
        
        if(value ==0)
            sprintf(output,"    %-10s__",txt );
        else 
            sprintf(output,"    %-10s%+2d",txt , (char)value); 
        
    }
    PrintInfo(output);
  
    
}

void DisplayBase::Print(PowerLink PL)
 {

     if(PL.Command == 59)
    {
      PrintAudio(PL.Audio.Device,PL.Audio.ValueType,PL.Audio.Seek,PL.Audio.Value);
      return;
    }
    else if (PL.Command == 51)
    {
        SetSound_Org(PL.Data,PL.Sound.Type,PL.Sound.SubType,PL.Sound.Value);
    }
 }

void DisplayBase::PrintInfo(int out) 
{   char output[50]; 
    sprintf(output,"%d",out);
    PrintInfo(output);
}
void DisplayBase::PrintInfo(char* left,char * main,char * right)
{ 
    char output[50]; 
    sprintf(output,"%-2s  %-*s   %s",left,8,main,right); 
    PrintInfo(output);
    
}
void DisplayBase::PrintInfo(int left,char * main,char * right)
{
    char output[50];
    sprintf(output,"%-2d  %-10s%2s",left,main,right);
    PrintInfo(output);

}

void DisplayBase::PrintInfo(int left,char * main, int right)
{
    char output[50]; 
    sprintf(output,"%-2d  %-10s%2d",left,main,right); 
    PrintInfo(output);
}
void DisplayBase::PrintInfo(char* left,char * main,int right)
{
    char output[50]; 
    sprintf(output,"%-2s  %-10s%2d",left,main,right); 
    PrintInfo(output);
}
