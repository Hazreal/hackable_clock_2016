#include "clock_defs.h"
#include "ds1302.h"

/*
 * initialize the ds1302 registers and set the default time and date
 * zero the 31 bytes of scratchpad ram with a burst write
 * (erase and invalidate)
 * the RTC supports individual byte access to ram, we always use
 * burst I/O
  to be removed
 */
void defaultRTC(ubyte mon, ubyte day, ubyte yr, ubyte dow, 
  ubyte hr, ubyte min, ubyte sec)
{
 ubyte data[31];
 
  set_direction(RTC_CLK, PIN_OUT);
  set_direction(RTC_DAT, PIN_OUT); 
  set_direction(RTC_CE, PIN_OUT);
   
  data[0] = ('\0');
  writeRTC(CMD_WRITE_WP, data, 1);
 
  data[0] = 0xA5; /* trickle charger on with 1 diode, 2K ohms */
  writeRTC(CMD_WRITE_TCS, data, 1);
  
  writeTime(hr, min, sec);
  writeDate(mon, day, yr, dow);
  
  memset(data, '\0', 31);
  writeRTC(CMD_WRITE_RAM, data, 31);
}  

/* write 31 bytes of data to the scratchpad RAM */
void saveConfig(ubyte data[])
{
    data[0] = 0xAA;
    writeRTC(CMD_WRITE_RAM, data, 31);
}

/* read 31 bytes of data from the scratchpad RAM */
int getConfig(ubyte data[])
{
  memset(data, '\0', 31);
  readRTC(CMD_READ_RAM, data, 31);
  return (data[0] == 0xAA);  
}

void writeTime(ubyte hr, ubyte min, ubyte sec)
{
  ubyte data[1];
 
  data[0] = bin2bcd(hr) & 0x3F; /* Enable 24 hr mode */
  writeRTC(RTC_WRITE_HRS, data, 1); 
  data[0] = bin2bcd(min);
  writeRTC(RTC_WRITE_MINS, data, 1);
  data[0] = bin2bcd(sec) & 0x7F; /* clock halt disabled */
  writeRTC(RTC_WRITE_SECS, data, 1);
}  

void readTime(ubyte *hr, ubyte *min, ubyte *sec)
{
  ubyte data[1] = {'\0'};
  
  readRTC(RTC_READ_HRS, data, 1);
  *hr = bcd2bin(data[0]); 
  readRTC(RTC_READ_MINS, data, 1);
  *min = bcd2bin(data[0]);
  readRTC(RTC_READ_SECS, data, 1);
  *sec = bcd2bin(data[0]);
}  

void writeDate(ubyte month, ubyte day, ubyte year, ubyte dow)
{
  ubyte data[1];
  
  data[0] = bin2bcd(month);
  writeRTC(RTC_WRITE_MTH, data, 1);
  data[0] = bin2bcd(day);
  writeRTC(RTC_WRITE_DAY, data, 1);
  data[0] = bin2bcd(year);
  writeRTC(RTC_WRITE_YR, data, 1);
  data[0] = bin2bcd(dow);
  writeRTC(RTC_WRITE_DOW, data, 1);  
}  

void readDate(ubyte *month, ubyte *day, ubyte *year, ubyte *dow)
{
  ubyte data[1] = ("\0");
  
  readRTC(RTC_READ_MTH, data, 1);
  *month = bcd2bin(data[0]);
  readRTC(RTC_READ_DAY, data, 1);
  *day = bcd2bin(data[0]);
  readRTC(RTC_READ_YR, data, 1);
  *year = bcd2bin(data[0]);
  readRTC(RTC_READ_DOW, data, 1);
  *dow = bcd2bin(data[0]); 
}  

void writeRTC(ubyte command, ubyte data[], ubyte dataLen)
{
    high(RTC_CE);
    for(int i=0; i<8; i++)
    {
        if (command & 0x01)
            high(RTC_DAT);
        else
            low(RTC_DAT);
        high(RTC_CLK);
        command = command >> 1;
        low(RTC_CLK);
    }
}
void readRTC(ubyte command, ubyte data[], ubyte datalen)
{
    high(RTC_CE);
    for(int i=0; i<8; i++)
    {
        if (command & 0x01)
            high(RTC_DAT);
        else
            low(RTC_DAT);
        high(RTC_CLK);
        command = command >> 1;
        low(RTC_CLK);
    }
    
    set_direction(RTC_DAT, PIN_IN);
    for (int i=0; i<datalen; i++)
    {
        ubyte newByte = '\0';
        for(int j=0; j<8; j++)
        {
            if (input(RTC_DAT) == 1)
                newByte = (newByte << 1) + 1;
            else
                newByte = (newByte << 1);
            high(RTC_CLK);
            low(RTC_CLK);
        }
        data[i] = reverseByte(newByte);
    }
    set_direction(RTC_DAT, PIN_OUT);
    low(RTC_CE);
}

ubyte reverseByte(ubyte byte)
{
    ubyte newByte = '\0';
    
    for(int i=0; i<8; i++)
    {
        if (byte & 0x01)
            newByte = (newByte << 1) + 1;
        else
            newByte = (newByte << 1);
        byte = byte >> 1;
    }
    return newByte;
}
