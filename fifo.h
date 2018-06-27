#ifndef _FIFO_H_
#define _FIFO_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* Change the size of the fifo easily (assuming size is constant) */
#define FIFO_SIZE	5

/* Change the type of data contained in the fifo easily */
typedef unsigned char fifoType;

enum{
	false,
	true,
};

struct s_fifo
{
	int size;
	fifoType msgList[FIFO_SIZE];
	int tail;//read position pointer
	int head;//write position pointer
	int nbData;
};


void init(int size);
int fifo_push(fifoType* data);
int fifo_forcePush(fifoType* data)
int fifo_checkData(int index, fifoType* data);
int fifo_pop(fifoType* data);
int fifo_isEmpty(void);
int fifo_isFull(void);


#endif //_FIFO_H_
