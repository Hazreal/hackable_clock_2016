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

int main()
{

  ubyte month=1, day=1, year=16;
  ubyte dow=6;
  ubyte hour=12, minute=0, second=0;

  ubyte alarmHour=12, alarmMinute=0;

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
  
  freqout(1,500, 1000);
  freqout(1,500, 1500);
  
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
    readTime(&hour, &minute, &second);
printf("%d:%d:%d\n",hour, minute, second);
pause(500);

    if (minute != lastMinute)
    {
      /*
       * update LED display, see datasheet for display codes
       * clock is in 24-hour mode, adjust output to 12-hour mode
      */
dprint(ledDisplay, "1111");
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
    }

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
    freqout(1,2000, 1046.5);
    freqout(1,2000, 1568.0);
    freqout(1,500, 1396.9);
    freqout(1,500, 1318.5);
    freqout(1,500, 1174.7);
    freqout(1,2000, 2093.0);
    freqout(1,2000, 1568.0);
    freqout(1,500, 1396.9);
    freqout(1,500, 1318.5);
    freqout(1,500, 1174.7);
    freqout(1,2000, 2093.0);
    freqout(1,2000, 1568.0);
    freqout(1,500, 1396.9); //fix this section
    freqout(1,500, 1318.5);
    freqout(1,500, 1396.9);
    freqout(1,2000, 1046.5);
    pause(5000);
}  

