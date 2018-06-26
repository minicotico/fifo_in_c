#ifndef _FIFO_H_
#define _FIFO_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0


/* Change the size of the fifo easily (assuming size is constant) */
#define FIFO_SIZE	4
/* Change the type of data contained in the fifo easily */
typedef unsigned char fifoType;

struct s_fifo
{
	int size;
	fifoType msgList[FIFO_SIZE];
	int tail;//read position pointer
	int head;//write position pointer
};


void init(int size);
int push(fifoType* data);
int checkData(int index, fifoType* data);
void pop(fifoType* data);
int isEmpty(void);
int isFull(void);


#endif //_FIFO_H_
