/*
 * Hackable Clock Project 2016-17
 * Clock driver (main program file)
 *
*/
#include "simpletools.h"
#include "simpletext.h"
#include "serial.h"
#include "clock_defs.h"
#include "ds1302.h"

/*
 * create 3 user-defined functions
 * setTime, setAlarm, soundAlarm
 *
 * all of the RTC functionality is in ds1302.h and ds1302.c
 * it is included above
 *
 * you may use the print() function while debugging to output to the serial console
*/


void soundAlarm();
int setTime(ubyte hour, ubyte minute, serial *display);
void setAlarm(ubyte *hour, ubyte *minute, serial *display);

int main()
{

  ubyte month=1, day=1, year=16;
  ubyte dow=6;
  ubyte hour=12, minute=0, second=0;

  ubyte alarmHour=13, alarmMinute=0;

  ubyte config[31];           /* scratchpad ram is 31 bytes, used to store config */
                              /* first byte is the config valid flag, don't touch */
                              /* remaining 30 bytes may be used to store anything */
  serial *ledDisplay;
  int *alarmCog=NULL;
  ubyte lastMinute=255;        /* the last minute that the LED display was updated */
  
  set_direction(DISPLAY, PIN_OUT);
  ledDisplay = serial_open(-1, DISPLAY, 0, 9600);

  writeChar(ledDisplay, 0x76);
  dprint(ledDisplay, "8888");
  writeChar(ledDisplay, 0x77);
  writeChar(ledDisplay, 0x3F);
    
 // freqout(11, 100, 1000); 
 // freqout(11, 100, 3000);
  /*
   * initialize the LED display, set pin direction (88:88 start message)
   * set pin directions on buttons, switch, and speaker (beep-boop speaker)
   * read scratchpad RAM and check clock config flag
   * if flag is true
   *   restore clock config from scratchpad RAM
   * else
   *   set RTC pin directions
   *   set RTC write bit, disable halt flag, and enable trickle charger
   *   set RTC default time and date
   *   clear scratchpad RAM
  */
  if (getConfig(config))
  {
    alarmHour = config[1];
    alarmMinute = config[2];
  }
  else
    defaultRTC(month, day, year, dow, hour, minute, second);
    
  /* wait for circuits to settle before starting clock operation */
  pause(250);

  /* infinite loop - start clock operation */
  while (1)
  {
//TODO REMOVE
  readTime(&hour, &minute, &second);
//printf("%d:%d:%d\n",hour, minute, second);
//pause(500);

    if (minute != lastMinute)
    {
      /*
       * update LED display, see datasheet for display codes
       * clock is in 24-hour mode, adjust output to 12-hour mode
      */
      writeChar(ledDisplay, 0x76);
      //writeChar(ledDisplay, 0x77);
      //writeChar(ledDisplay, 0x79);
      //writeChar(ledDisplay, 0x01);
      dprint(ledDisplay, "%d%02d", hour, minute);
    }

    if (input(ALRM_SWI) == SW_ON)
    {            
      if (second % 2 == 0)  // set alarm indicator on LED display to ON and "blink" colon
      {
        writeChar(ledDisplay, 0x77);
        writeChar(ledDisplay, 0x20);
      }
      else
      {
        writeChar(ledDisplay, 0x77);
        writeChar(ledDisplay, 0x10); 
      }           
      if (hour == alarmHour && minute == alarmMinute && !alarmCog) //sound alarm, start code in new cog
      {
        alarmCog = cog_run(soundAlarm, 16);
      }
    }
    
    else //Alarm Switch is off
    {
      writeChar(ledDisplay, 0x77);      //set alarm indicator on LED display to OFF and "blink" colon
      writeChar(ledDisplay, 0x00);    
    
      if (alarmCog) //stop alarm cog if alarm is beeping
      {
       cog_end(alarmCog);
       alarmCog = NULL;
      }        
    }    
      
    if (input(TIME_BTN) == BTN_DOWN)
    {
      /*
       * call set time function
       * save alarm time in scratchpad RAM
       * set valid flag in scratchpad RAM
       * set lastMinute to force screen update
      */
      setTime(hour, minute, ledDisplay);
      lastMinute = -1;
    }

    if (input(ALRM_BTN) == BTN_DOWN)
    {
      /*
       * call set alarm function
       * set alarmHour and alarmMinute
       * save alarm time in scratchpad RAM
       * set valid flag in scratchpad RAM
       * set lastMinute to force screen update
      */
      setAlarm(alarmHour, alarmMinute, ledDisplay);
      dprint(ledDisplay, "%d%02d", hour, minute);
    }
    print("%d:%02d %d:%02d \n", hour, minute, alarmHour, alarmMinute);
    lastMinute = minute;
    pause(250); // ### SHORTEN THIS TO 45ms FOR PRODUCTION AND REMOVE THIS COMMENT ###
  } /* end of while(1) */

  /*
   * execution should never get here
   * if it does print "HALt" on LED
  */
  writeChar(ledDisplay, 0x76);
  dprint(ledDisplay, "HALt");
  return 0;
}

//----------------------------------------------------------------------------------
// This function will kind of play Star Wars
void soundAlarm()
{
    // freqout(int pin,int ms, int frequency);
    freqout(11,2000, 1046.5);
    freqout(11,2000, 1568.0);
    freqout(11,500, 1396.9);
    freqout(11,500, 1318.5);
    freqout(11,500, 1174.7);
    freqout(11,2000, 2093.0);
    freqout(11,2000, 1568.0);
    freqout(11,500, 1396.9);
    freqout(11,500, 1318.5);
    freqout(11,500, 1174.7);
    freqout(11,2000, 2093.0);
    freqout(11,2000, 1568.0);
    freqout(11,500, 1396.9); //fix this section
    freqout(11,500, 1318.5);
    freqout(11,500, 1396.9);
    freqout(11,2000, 1046.5);
    pause(5000);
}  


/**********************************
 *switch display into time set mode
 *return true if time changed
***********************************/
int setTime(ubyte hour, ubyte minute, serial *display)
{
  ubyte hr = hour;
  ubyte min = minute;
  writeChar(display, 0x76);
  dprint(display, "%02d%02d", hr, min);
  
  while (input(TIME_BTN) == BTN_DOWN)
  {
    if (input(HOUR_BTN) == BTN_DOWN)
      hr = (hr + 1)%24;
    
    if (input(MNIT_BTN) == BTN_DOWN)
      min = (min+1)%60;
    
    writeChar(display, 0x79);
    writeChar(display, 0x00);
    dprint(display, "%02d%02d", hr, min);
    pause(250);         
  }
  int timeChanged = (hr != hour || min != minute);
  if (timeChanged)
    writeTime(hr, min, 0);
  
  return timeChanged;     
}
/***********************************
 *switchs display to show alarm mode
 *alters alarmHour and alarmMinute
 *by reference
 ***********************************/
void setAlarm(ubyte *hour, ubyte *minute, serial *display)
{
  ubyte hr = hour;
  ubyte min = minute;
  writeChar(display, 0x76);
  dprint(display, "%02d%02d", hr, min);
  
  while (input(ALRM_BTN) == BTN_DOWN)
  {
    //if (input(HOUR_BTN) == BTN_DOWN)
    //  hr = (hr + 1)%24;
    
    if (input(HOUR_BTN) == BTN_DOWN)
      min = (min+1)%60;
    
    writeChar(display, 0x79);
    writeChar(display, 0x00);
    dprint(display, "%02d%02d", hr, min);
    pause(250);         
  }  
  int alarmChanged = (hr != hour || min != minute);
  if (alarmChanged)
  {
    hour = hr;       
    minute = min;
  }  
}    