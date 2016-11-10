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

#define CMD_RITE_SECS 0x80
#define CMD_READ_SECS 0x81
#define CMD_RITE_MINS 0x82
#define CMD_READ_MINS 0x83
#define CMD_RITE_HOUR 0x84
#define CMD_READ_HOUR 0x85
#define CMD_RITE_DAY  0x86
#define CMD_READ_DAY  0x87
#define CMD_RITE_MON  0x88
#define CMD_READ_MON  0x89
#define CMD_RITE_DOW  0x8a
#define CMD_READ_DOW  0x8b
#define CMD_RITE_YEAR 0x8c
#define CMD_READ_YEAR 0x8d
#define CMD_WRITE_TCS 0x90

void writeRTC(unsigned char command, unsigned long data, unsigned short bits);

{
  int  bit;
  
  assert(bits < 32);
  
  high(RTC_CE)
  for(int x=0; x<8; x++)
  {
    bit = command & 0x01;
    output(RTC_DAT, bit)
    high(RTC_CLK);
    low(RTC_CLK);
    command = command >> 1;
  }
  
  for(int x=0; x<bits; x++)
  {
    bit = data & 0x01;
    low(RTC_CLK);
    output(RTC_DAT, bit)
    high(RTC_CLK);
    command = data >> 1;
  }      
    
  low(RTC_CE)
}  