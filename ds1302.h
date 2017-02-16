/*
ds1302 functions


defaultRTC
saveConfig
int getConfig

writeTime(hours, minutes, seconds)
readTime(addresses of those three variables)
writeDate
readDate

writeRTC
readRTC

reverseByte
bcd2bin (ubyte data)
    return((data & 0x0F) + (((data >> 4) & 0x0F) * 10)); // >> == bit shifting right; could also divide by 16 here
bin2bcd
    int tensDigit = data/10;
    return(data - (tensDigit * 10) + (tensDigit << 4)); 
    to be removed here
*/

/* ---------------------------------------------------------------------------------------
 * writes occur lsb first, reads occur lsb first - see DS1302 datasheet
*/


void writeRTC(ubyte command, ubyte data[], ubyte datalen)
{
  high(RTC_CE);
  
  for (int i=0; i<8; i++)
  {
    if (command & 0x01)
    {
      high(RTC_DAT);
    }
    
    else
    {
      low(RTC_DAT);
    }
    
    high(RTC_CLK);
    command = command >> 1;
    low(RTC_CLK); 
                
  }     
  
  for (int i=0; i<datalen; i++)
  {
    ubyte oneByte = data[i];
    for (int j=0; j<8; j++)
    {
          if (oneByte & 0x01)
    {
      high(RTC_DAT);
    }
    
    else
    {
      low(RTC_DAT);
    }
    
    high(RTC_CLK);
    oneByte = oneByte >> 1;
    low(RTC_CLK); 
       
  }
      
  low(RTC_CE); 
}   

/* ---------------------------------------------------------------------------------------
 * 
*/
ubyte bcd2bin (ubyte data)
{
  return((data & 0x0F) + (((data >> 4) & 0x0F) * 10)); // >> == bit shifting right; could also divide by 16 here
}    

/* ---------------------------------------------------------------------------------------
 * 
*/
ubyte bin2bcd (ubyte data)
{
  int tensDigit = data/10;
  return(data - (tensDigit * 10) + (tensDigit << 4)); 
}    

