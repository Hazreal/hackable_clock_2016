/*
 * Hackable Clock Project 2016-17
 * Microcontroller pin names and other handy names for things
 *
*/
#ifndef CLOCK_H
#define CLOCK_H

/* user defined types */
typedef unsigned char ubyte;

/* button states */
#define BTN_DOWN 1
#define BTN_UP   0

/* switch states */
#define SW_ON  1
#define SW_OFF 0

/* cpu pin directions */
#define PIN_IN  0
#define PIN_OUT 1

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

/* real time clock commands */
#define RTC_WRITE_SECS 0x80
#define RTC_READ_SECS  0x81
#define RTC_WRITE_MINS 0x82
#define RTC_READ_MINS  0x83
#define RTC_WRITE_HRS  0x84
#define RTC_READ_HRS   0x85
#define RTC_WRITE_DAY  0x86
#define RTC_READ_DAY   0x87
#define RTC_WRITE_MTH  0x88
#define RTC_READ_MTH   0x89
#define RTC_WRITE_DOW  0x8A
#define RTC_READ_DOW   0x8B
#define RTC_WRITE_YR   0x8C
#define RTC_READ_YR    0x8D

#define CMD_WRITE_WP   0x8E
#define CMD_WRITE_TCS  0x90

#define CMD_WRITE_RAM  0xFE
#define CMD_READ_RAM   0xFF

#endif
