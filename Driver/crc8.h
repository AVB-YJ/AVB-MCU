/***********************************************************/
/* File Name: crc8.h*/
/**/
/* Date: 2014-11-17*/
/***********************************************************/
#ifndef CRC8_H
#define CRC8_H

extern unsigned char crc8 ( const void *data, unsigned char len );

extern const unsigned char CRC8Table[256];

#endif

