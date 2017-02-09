

/*
 * initialize the ds1302 registers and set the default time and date
 * zero the 31 bytes of scratchpad memory
 */

void defaultRTC(

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

void writeTime(

void readTime(

void writeDate(

void readDate(

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
    ubyte newByte = '\0'
    
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
