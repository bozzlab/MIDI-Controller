#include "mbed.h"
#include "USBMIDI.h"
#include "TS_DISCO_F746NG.h"
#include "LCD_DISCO_F746NG.h"

#define FastSpeedInterface 0
#define HighSpeedInterface 1

LCD_DISCO_F746NG lcd;
TS_DISCO_F746NG ts;
USBMIDI midi(FastSpeedInterface);
Serial pc(USBTX,USBRX);

/////////////////
int main()
{
    TS_StateTypeDef TS_State;
    uint8_t text[30];
    uint8_t status;
    uint8_t idx;
    uint8_t cleared = 0;
    uint8_t prev_nb_touches = 0;
    
    lcd.SetFont(&Font24);
    lcd.DisplayStringAt(0, LINE(3), (uint8_t *)"MIDI Controller [X1]", CENTER_MODE);
         lcd.DisplayStringAt(0, LINE(5), (uint8_t *)"By ", CENTER_MODE);
     lcd.DisplayStringAt(0, LINE(8), (uint8_t *)"[Bozz Striker] [Nut] [Tos]", CENTER_MODE);
      lcd.DisplayStringAt(0, LINE(10), (uint8_t *)"1 May 2018", CENTER_MODE);
    wait(3);

    status = ts.Init(lcd.GetXSize(), lcd.GetYSize());
    if (status != TS_OK) {
        lcd.Clear(LCD_COLOR_RED);
        lcd.SetBackColor(LCD_COLOR_RED);
        lcd.SetTextColor(LCD_COLOR_WHITE);
        lcd.DisplayStringAt(0, LINE(5), (uint8_t *)"TOUCHSCREEN INIT FAIL", CENTER_MODE);
    } else { ////////////////////////////////// TAG ///////////////////////////////////
         lcd.SetFont(&Font16);
        lcd.Clear(LCD_COLOR_BLACK);
            
       
        ///////////////////////  Pad /////////////////////////
    lcd.SetTextColor(LCD_COLOR_WHITE); // C note
    lcd.DrawRect(10,190, 80,60);
     lcd.SetTextColor(LCD_COLOR_GREEN); 
    lcd.FillRect(20,200,60,40);
    
     lcd.SetTextColor(LCD_COLOR_WHITE); // C# note
    lcd.DrawRect(100,190, 80,60);
          lcd.SetTextColor(LCD_COLOR_ORANGE); 
    lcd.FillRect(110,200,60,40);
 
 lcd.SetTextColor(LCD_COLOR_WHITE); // D note
    lcd.DrawRect(190,190, 80,60);
           lcd.SetTextColor(LCD_COLOR_GREEN); 
    lcd.FillRect(200,200,60,40);
 
 lcd.SetTextColor(LCD_COLOR_WHITE); // D% note
    lcd.DrawRect(280,190, 80,60);
      lcd.SetTextColor(LCD_COLOR_ORANGE); 
    lcd.FillRect(290,200,60,40);

 lcd.SetTextColor(LCD_COLOR_WHITE); // E note
    lcd.DrawRect(370,190, 80,60);
       lcd.SetTextColor(LCD_COLOR_GREEN); 
    lcd.FillRect(380,200,60,40);
 
  lcd.SetTextColor(LCD_COLOR_WHITE); // F note
    lcd.DrawRect(10,120, 80,60);
      lcd.SetTextColor(LCD_COLOR_GREEN); 
    lcd.FillRect(20,130,60,40);
    
     lcd.SetTextColor(LCD_COLOR_WHITE); // F# note
    lcd.DrawRect(100,120, 80,60);
           lcd.SetTextColor(LCD_COLOR_ORANGE); 
    lcd.FillRect(110,130,60,40);
 
 lcd.SetTextColor(LCD_COLOR_WHITE); // G note
    lcd.DrawRect(190,120, 80,60);
     lcd.SetTextColor(LCD_COLOR_GREEN); 
    lcd.FillRect(200,130,60,40);

 lcd.SetTextColor(LCD_COLOR_WHITE); // G% note
    lcd.DrawRect(280,120, 80,60);
    lcd.SetTextColor(LCD_COLOR_ORANGE); 
    lcd.FillRect(290,130,60,40);
 
 lcd.SetTextColor(LCD_COLOR_WHITE); // A note
    lcd.DrawRect(370,120, 80,60);
      lcd.SetTextColor(LCD_COLOR_GREEN); 
    lcd.FillRect(380,130,60,40);
 
  lcd.SetTextColor(LCD_COLOR_WHITE); // A# note
    lcd.DrawRect(190,50, 80,60);
 lcd.SetTextColor(LCD_COLOR_ORANGE); 
    lcd.FillRect(200,60,60,40);

 lcd.SetTextColor(LCD_COLOR_WHITE); // B note
    lcd.DrawRect(280,50, 80,60);
       lcd.SetTextColor(LCD_COLOR_GREEN); 
    lcd.FillRect(290,60,60,40);
 
 lcd.SetTextColor(LCD_COLOR_WHITE); // C note
    lcd.DrawRect(370,50, 80,60);
  lcd.SetTextColor(LCD_COLOR_CYAN); 
    lcd.FillRect(380,60,60,40);

 //PITCH  ////
 
  lcd.SetTextColor(LCD_COLOR_WHITE); // C note
    lcd.DrawRect(10,50,170,60);
     lcd.SetTextColor(LCD_COLOR_MAGENTA); 
    lcd.FillRect(20,60,150,40);

///// TAG MIDI NUM

    
////// TIME  
  lcd.SetTextColor(LCD_COLOR_WHITE); // C note
    lcd.DrawRect(300,0,150,35);
 
        lcd.SetTextColor(LCD_COLOR_BLUE);
        lcd.FillRect(310,5,130,25); 
        
    
  
//////////////////////////////// MIDI Message///////
    int i = 60; 
    int vol= 64;
    
    
    while(1) {
    int x,y,x2,y2;
   
    ts.GetState(&TS_State);
    if ((TS_State.touchDetected))
    {
       // Clear lines corresponding to old touches coordinates
            if (TS_State.touchDetected < prev_nb_touches) {
                for (idx = (TS_State.touchDetected + 1); idx <= 5; idx++) {
                    //lcd.ClearStringLine(idx);
                }
            }
            prev_nb_touches = TS_State.touchDetected;
            

            cleared = 0;
            
            x = TS_State.touchX[0];
            y = TS_State.touchY[0];
            x2 = TS_State.touchX[1];
            y2 = TS_State.touchY[1];
     
    pc.printf("Touch x =%3d : y= %3d\r\n",x,y);     
       wait(0.01);
       
       ////MIDI NUM 
 
       if (x < 80 && x> 10 && y<110 && y>60) 
     {
          i--; 
          wait(0.1);
         }
       else if (x < 170 && x> 80 && y<110 && y>60) 
   {
          i++; 
          wait(0.1);
         }
               
 //   sprintf((char*)text, "MIDI Num %d ", i); //display num
       //  lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);


      if(x< 430 && x>365 && y<40 && y>0) 
              {
               vol++;
                wait(0.1);

               }
               
               else if(x<360 && x>300 && y<40 && y>0)
               {
                   vol--;
                   wait(0.1);

                   }
                    sprintf((char*)text, "MIDI Num %d :: Velo. %d ", i,vol); //display num
          lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);


      ///time   

      
      /////note 
          if( x<80 && x>10  && y<250 && y>190) // C note
          {
            
            midi.write(MIDIMessage::NoteOn(i,vol,0));  ///midi send
            lcd.SetTextColor(LCD_COLOR_RED); // display
            lcd.FillRect(20,200,60,40); // display
              if (x2 < 80 && x2> 10 && y2<110 && y2>60) i--; //down note
                else if (x2 < 170 && x2> 80 && y2<110 && y2>60) i++; //up midi
              if(x2< 430 && x2>365 && y2<40 && y2>0) vol++; // up vol
               else if(x2<360 && x2>300 && y2<40 && y2>0)vol--; // down vol 
                   sprintf((char*)text, "MIDI Num %d :: Velo. %d ", i,vol); //display num
         lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);  //display num
            
       // midi.write(MIDIMessage::PitchWheel(Pitch(),0)); 
        //wait(TS_State.touchDetected);
        wait(0.2); //time
              }
              
         else if(x<170 && x>110  && y<250 && y>200) // C# note
          {
            midi.write(MIDIMessage::NoteOn(i+1,vol,0)); 
            lcd.SetTextColor(LCD_COLOR_RED); 
            lcd.FillRect(110,200,60,40);
           if (x2 < 80 && x2> 10 && y2<110 && y2>60) i--; //down note
                else if (x2 < 170 && x2> 80 && y2<110 && y2>60) i++; //up midi
              if(x2< 430 && x2>365 && y2<40 && y2>0) vol++; // up vol
               else if(x2<360 && x2>300 && y2<40 && y2>0)vol--; // down vol 
                   sprintf((char*)text, "MIDI Num %d :: Velo. %d ", i+1,vol); //display num
         lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);  //display num
             wait(0.2);//wait(TS_State.touchDetected);
              }
              
         else if(x<250 && x>210  && y<250 && y>200) // D note
          {
         midi.write(MIDIMessage::NoteOn(i+2,vol,0)); 
         lcd.SetTextColor(LCD_COLOR_RED); 
         lcd.FillRect(200,200,60,40);
             if (x2 < 80 && x2> 10 && y2<110 && y2>60) i--; //down note
                else if (x2 < 170 && x2> 80 && y2<110 && y2>60) i++; //up midi
              if(x2< 430 && x2>365 && y2<40 && y2>0) vol++; // up vol
               else if(x2<360 && x2>300 && y2<40 && y2>0)vol--; // down vol 
                   sprintf((char*)text, "MIDI Num %d :: Velo. %d ", i+2,vol); //display num
         lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);  //display num
          wait(0.2);//wait(TS_State.touchDetected);
              }
              
         else if(x<355 && x>290  && y<250 && y>200) // D# note
          {
           midi.write(MIDIMessage::NoteOn(i+3,vol,0)); 
           lcd.SetTextColor(LCD_COLOR_RED); 
           lcd.FillRect(290,200,60,40);
              if (x2 < 80 && x2> 10 && y2<110 && y2>60) i--; //down note
                else if (x2 < 170 && x2> 80 && y2<110 && y2>60) i++; //up midi
              if(x2< 430 && x2>365 && y2<40 && y2>0) vol++; // up vol
               else if(x2<360 && x2>300 && y2<40 && y2>0)vol--; // down vol 
                   sprintf((char*)text, "MIDI Num %d :: Velo. %d ", i+3,vol); //display num
         lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);  //display num
           wait(0.2);//wait(TS_State.touchDetected);
              }
              
         else if(x<450 && x>370  && y<250 && y>200) // E note
          {
          midi.write(MIDIMessage::NoteOn(i+4,vol,0)); 
           lcd.SetTextColor(LCD_COLOR_RED); 
          lcd.FillRect(380,200,60,40);
          if (x2 < 80 && x2> 10 && y2<110 && y2>60) i--; //down note
                else if (x2 < 170 && x2> 80 && y2<110 && y2>60) i++; //up midi
              if(x2< 430 && x2>365 && y2<40 && y2>0) vol++; // up vol
               else if(x2<360 && x2>300 && y2<40 && y2>0)vol--; // down vol 
                   sprintf((char*)text, "MIDI Num %d :: Velo. %d ", i+4,vol); //display num
         lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);  //display num
       wait(0.2);//wait(TS_State.touchDetected);
              }
              
           else if(x<80 && x>10  && y<175 && y>135) // F note
          {
             midi.write(MIDIMessage::NoteOn(i+5,vol,0)); 
                  lcd.SetTextColor(LCD_COLOR_RED); 
                lcd.FillRect(20,130,60,40);
                    if (x2 < 80 && x2> 10 && y2<110 && y2>60) i--; //down note
                else if (x2 < 170 && x2> 80 && y2<110 && y2>60) i++; //up midi
              if(x2< 430 && x2>365 && y2<40 && y2>0) vol++; // up vol
               else if(x2<360 && x2>300 && y2<40 && y2>0)vol--; // down vol 
                   sprintf((char*)text, "MIDI Num %d :: Velo. %d ", i+5,vol); //display num
         lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);  //display num
               wait(0.2);//wait(TS_State.touchDetected);
              }
              
                else if(x<170 && x>100  && y<175 && y>135) // F# note
          {
         midi.write(MIDIMessage::NoteOn(i+6,vol,0)); 
            lcd.SetTextColor(LCD_COLOR_RED); 
             lcd.FillRect(110,130,60,40);
              if (x2 < 80 && x2> 10 && y2<110 && y2>60) i--; //down note
                else if (x2 < 170 && x2> 80 && y2<110 && y2>60) i++; //up midi
              if(x2< 430 && x2>365 && y2<40 && y2>0) vol++; // up vol
               else if(x2<360 && x2>300 && y2<40 && y2>0)vol--; // down vol 
                   sprintf((char*)text, "MIDI Num %d :: Velo. %d ", i+6,vol); //display num
         lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);  //display num
                wait(0.2);//wait(TS_State.touchDetected);
              }
                   
                else if(x<260 && x>190  && y<175 && y>135) // G note
          {
        midi.write(MIDIMessage::NoteOn(i+7,vol,0)); 
         lcd.SetTextColor(LCD_COLOR_RED); 
         lcd.FillRect(200,130,60,40);
             if (x2 < 80 && x2> 10 && y2<110 && y2>60) i--; //down note
                else if (x2 < 170 && x2> 80 && y2<110 && y2>60) i++; //up midi
              if(x2< 430 && x2>365 && y2<40 && y2>0) vol++; // up vol
               else if(x2<360 && x2>300 && y2<40 && y2>0)vol--; // down vol 
                   sprintf((char*)text, "MIDI Num %d :: Velo. %d ", i+7,vol); //display num
         lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);  //display num
            wait(0.2);//wait(TS_State.touchDetected);
              }   
                
                else if(x<360 && x>270  && y<175 && y>135) // G# note
          {
        midi.write(MIDIMessage::NoteOn(i+8,vol,0)); 
        lcd.SetTextColor(LCD_COLOR_RED); 
      lcd.FillRect(290,130,60,40);
        if (x2 < 80 && x2> 10 && y2<110 && y2>60) i--; //down note
                else if (x2 < 170 && x2> 80 && y2<110 && y2>60) i++; //up midi
              if(x2< 430 && x2>365 && y2<40 && y2>0) vol++; // up vol
               else if(x2<360 && x2>300 && y2<40 && y2>0)vol--; // down vol 
                   sprintf((char*)text, "MIDI Num %d :: Velo. %d ", i+8,vol); //display num
         lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);  //display num
           wait(0.2);//wait(TS_State.touchDetected);
              }
                   
                else if(x<435 && x>370  && y<175 && y>135) // A note
          {
        midi.write(MIDIMessage::NoteOn(i+9,vol,0)); 
            lcd.SetTextColor(LCD_COLOR_RED); 
         lcd.FillRect(380,130,60,40);
              if (x2 < 80 && x2> 10 && y2<110 && y2>60) i--; //down note
                else if (x2 < 170 && x2> 80 && y2<110 && y2>60) i++; //up midi
              if(x2< 430 && x2>365 && y2<40 && y2>0) vol++; // up vol
               else if(x2<360 && x2>300 && y2<40 && y2>0)vol--; // down vol 
                   sprintf((char*)text, "MIDI Num %d :: Velo. %d ", i+9,vol); //display num
         lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);  //display num
               wait(0.2);//wait(TS_State.touchDetected);
              }
                   
                else if(x<270 && x>200  && y<110 && y>60) // A# note
          {
        midi.write(MIDIMessage::NoteOn(i+10,vol,0)); 
         lcd.SetTextColor(LCD_COLOR_RED); 
          lcd.FillRect(200,60,60,40);
          if (x2 < 80 && x2> 10 && y2<110 && y2>60) i--; //down note
                else if (x2 < 170 && x2> 80 && y2<110 && y2>60) i++; //up midi
              if(x2< 430 && x2>365 && y2<40 && y2>0) vol++; // up vol
               else if(x2<360 && x2>300 && y2<40 && y2>0)vol--; // down vol 
                   sprintf((char*)text, "MIDI Num %d :: Velo. %d ", i+10,vol); //display num
         lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);  //display num
           wait(0.2);//wait(TS_State.touchDetected);
              }
                   
                else if(x<350 && x>290  && y<110 && y>60) // B note
          {
        midi.write(MIDIMessage::NoteOn(i+11,vol,0)); 
          lcd.SetTextColor(LCD_COLOR_RED); 
            lcd.FillRect(290,60,60,40);
        if (x2 < 80 && x2> 10 && y2<110 && y2>60) i--; //down note
                else if (x2 < 170 && x2> 80 && y2<110 && y2>60) i++; //up midi
              if(x2< 430 && x2>365 && y2<40 && y2>0) vol++; // up vol
               else if(x2<360 && x2>300 && y2<40 && y2>0)vol--; // down vol 
                   sprintf((char*)text, "MIDI Num %d :: Velo. %d ", i+11,vol); //display num
         lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);  //display num
        wait(0.2);//wait(TS_State.touchDetected);
              }
                   
                else if(x<435 && x>370  && y<110 && y>60) // C note
          {
        midi.write(MIDIMessage::NoteOn(i+12,vol,0)); 
          lcd.SetTextColor(LCD_COLOR_BLUE); 
         lcd.FillRect(380,60,60,40);
          if (x2 < 80 && x2> 10 && y2<110 && y2>60) i--; //down note
                else if (x2 < 170 && x2> 80 && y2<110 && y2>60) i++; //up midi
              if(x2< 430 && x2>365 && y2<40 && y2>0) vol++; // up vol
               else if(x2<360 && x2>300 && y2<40 && y2>0)vol--; // down vol 
                   sprintf((char*)text, "MIDI Num %d :: Velo. %d ", i+12,vol); //display num
         lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);  //display num
      wait(0.2);//wait(TS_State.touchDetected);
              }
              
////////////////////// not touch /////////////      
      } 
      else
       {
          midi.write(MIDIMessage::AllNotesOff(0));
          TS_State.touchX[1] = 0;  
          TS_State.touchY[1] = 0;
          /////// ex-map ////
              lcd.SetTextColor(LCD_COLOR_WHITE); // C note
    lcd.DrawRect(10,190, 80,60);
     lcd.SetTextColor(LCD_COLOR_GREEN); 
    lcd.FillRect(20,200,60,40);
    
     lcd.SetTextColor(LCD_COLOR_WHITE); // C# note
    lcd.DrawRect(100,190, 80,60);
          lcd.SetTextColor(LCD_COLOR_ORANGE); 
    lcd.FillRect(110,200,60,40);
 
 lcd.SetTextColor(LCD_COLOR_WHITE); // D note
    lcd.DrawRect(190,190, 80,60);
           lcd.SetTextColor(LCD_COLOR_GREEN); 
    lcd.FillRect(200,200,60,40);
 
 lcd.SetTextColor(LCD_COLOR_WHITE); // D% note
    lcd.DrawRect(280,190, 80,60);
      lcd.SetTextColor(LCD_COLOR_ORANGE); 
    lcd.FillRect(290,200,60,40);

 lcd.SetTextColor(LCD_COLOR_WHITE); // E note
    lcd.DrawRect(370,190, 80,60);
       lcd.SetTextColor(LCD_COLOR_GREEN); 
    lcd.FillRect(380,200,60,40);
 
  lcd.SetTextColor(LCD_COLOR_WHITE); // F note
    lcd.DrawRect(10,120, 80,60);
      lcd.SetTextColor(LCD_COLOR_GREEN); 
    lcd.FillRect(20,130,60,40);
    
     lcd.SetTextColor(LCD_COLOR_WHITE); // F# note
    lcd.DrawRect(100,120, 80,60);
           lcd.SetTextColor(LCD_COLOR_ORANGE); 
    lcd.FillRect(110,130,60,40);
 
 lcd.SetTextColor(LCD_COLOR_WHITE); // G note
    lcd.DrawRect(190,120, 80,60);
     lcd.SetTextColor(LCD_COLOR_GREEN); 
    lcd.FillRect(200,130,60,40);

 lcd.SetTextColor(LCD_COLOR_WHITE); // G% note
    lcd.DrawRect(280,120, 80,60);
    lcd.SetTextColor(LCD_COLOR_ORANGE); 
    lcd.FillRect(290,130,60,40);
 
 lcd.SetTextColor(LCD_COLOR_WHITE); // A note
    lcd.DrawRect(370,120, 80,60);
      lcd.SetTextColor(LCD_COLOR_GREEN); 
    lcd.FillRect(380,130,60,40);
 
  lcd.SetTextColor(LCD_COLOR_WHITE); // A# note
    lcd.DrawRect(190,50, 80,60);
 lcd.SetTextColor(LCD_COLOR_ORANGE); 
    lcd.FillRect(200,60,60,40);

 lcd.SetTextColor(LCD_COLOR_WHITE); // B note
    lcd.DrawRect(280,50, 80,60);
       lcd.SetTextColor(LCD_COLOR_GREEN); 
    lcd.FillRect(290,60,60,40);
 
 lcd.SetTextColor(LCD_COLOR_WHITE); // C note
    lcd.DrawRect(370,50, 80,60);
  lcd.SetTextColor(LCD_COLOR_CYAN); 
    lcd.FillRect(380,60,60,40);

 //PITCH  ////
 
  lcd.SetTextColor(LCD_COLOR_WHITE); // C note
    lcd.DrawRect(10,50,170,60);
     lcd.SetTextColor(LCD_COLOR_MAGENTA); 
    lcd.FillRect(20,60,150,40);

///// TAG

     lcd.SetBackColor(LCD_COLOR_MAGENTA);
     lcd.SetTextColor(LCD_COLOR_BLACK); 
  wait(0.1);        
                               
           }
                  }
                  }
                  }
