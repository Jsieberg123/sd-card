#ifndef SPI_H_
#define SPI_H_

#define IOBUFSIZE 256

extern volatile char iobuffer[IOBUFSIZE];

void SetupSpi();

#endif