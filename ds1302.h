#ifndef DS1302_H
#define DS1302_H

void defaultRTC(ubyte mon, ubyte day, ubyte yr, ubyte dow, ubyte hr, ubyte min, ubyte sec);
void saveConfig(ubyte data[]);
int getConfig(ubyte data[]);
void writeTime(ubyte hr, ubyte min, ubyte sec);
void readTime(ubyte *hr, ubyte *min, ubyte *sec);
void writeDate(ubyte month, ubyte day, ubyte year, ubyte dow);
void readDate(ubyte *month, ubyte *day, ubyte *year, ubyte *dow);
void writeRTC(ubyte command, ubyte data[], ubyte dataLen);
void readRTC(ubyte command, ubyte data[], ubyte datalen);
ubyte reverseByte(ubyte byte);
ubyte bin2bcd (ubyte data);
ubyte bcd2bin (ubyte data);

#endif