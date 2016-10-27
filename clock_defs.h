/*
 *Hackable Clock 2016-17
 *Common definitions for all code
 *AR, 10/26/2016
 */

#ifndef CLOCK_DEF_H
#define CLOCK_DEF_H

/* buttons and switches */
#define HOUR_BTN 16
#define MNIT_BTN 17
#define TIME_BTN 18
#define ALRM_BTN 0
#define ALRM_SWI 1

#define SPEAKER 11
#define DISPLAY 12

/* timekeeping chip pins */
#define RTC_CLK 13
#define RTC_DAT 14
#define RTC_CE  15

/* button states */
#define UP   0
#define DOWN 1

/* switch states */
#define ON  1
#define OFF 0

#endif