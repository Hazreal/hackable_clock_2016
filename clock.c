/*
 *Hackable Clock 2016-17
 *Main Clock Driver
 *AR, 10/26/2016
 */

#include "simpletools.h"
#include "clock_defs.h"

int checkSwitch(int sw_num);
int checkbutton(int btn_num);

int main()
{
  int hour=12, minute=0, second=0;
  int month=1, day=1, year=16;
  int dow=6;

  int alarmHourSet=-1, alarmMinuteSet=-1;
  int alarmHour=-1, alarmMinute=-1;
  int lastMinute=-1;
 /*
  *initialize LED
  *read the scratchpad RAM and check the clock configuration flag
  *if flag is true then load clock configuration from scratchpad RAM
  * else set default clock configuration (24 hour mode, trickle charger)
 */

  while(1)
  {
   /*
    *get current hour, minute, seconds from RTC
   */
   if (minute != lastMinute)
   {
    /*
     *update LED display
     *lastMinute = minute;
    */
   }

   if (checkSwitch(ALRM_SWI) == ON)
   {
     /*
      *set alarm indicator ON
     */
     if (hour == alarmHour && minute == alarmMinute)
     {
       /*
        *sound alarm, freqout function
       */
       if (checkButton(TIME_BTN) == DOWN)
       {
         /*
         *Sleep alarm for 15 minutes
         */
         alarmMinute += 15;
         if(alarmMinute >= 60){
           alarmMinute -= 60
           alarmHour += 1;
           FREQOUT 11, 1000, 2500;
         }

       }
     }

   }
   else
   {
    /*
     *set alarm indicator off
    */
    if (checkbutton(ALRM_BTN) == DOWN)
    {
      /*
       *Call set alarm Function
       *Update the alarmHour and alarmMinute variables
       *save alarm times in teh scratchpad RAM
       *set the valid flag in scratchpad RAM
      */
    }
    if (checkbutton(TIME_BTN) == DOWN)
    {
      /*
       *Call set time Function
       *Update the Hour and Minute and second variables
       *update real time clock with new time
      */
    }
    
    /*
    *set alarmMinute and alarmHour to alarmMinuteSet and alarmMinuteSet
    */
    alarmHour = alarmHourSet;
    alarmMinute = alarmMinuteSet;
   }

  } /*end of while(1)*/

  /*Code never gets here, if it does print "HALT" on LED */
  return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*Return the state of the alarm switch, on is true, off is false*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int checkSwitch(int sw_num)
{
  return (input(sw_num) == on);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*Return the state of the named switch, down is true, up is false*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int checkButton(int btn_num)
{
  return (input(btn_num) == down;
}
