/*
 * fifo.c
 *
 * Copyright (C) 2018 - Nicolas SIMON
 *
 *  is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 *  is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with . If not, see <http://www.gnu.org/licenses/>.
 */



#include "fifo.h"


struct s_fifo fifo;


/*
* Initialize the FIFO 
*
* Size is fix for now
*/
void init(int size)
{
	size++;
	fifo.size = FIFO_SIZE;
	fifo.tail = -1;
	fifo.head = 0;
	fifo.nbData = 0;
	memset(&fifo.msgList, 0, sizeof(fifoType)*FIFO_SIZE);
}




/**************************************************
* NAME : fifo_push
* BRIEF : push data into the fifo. Increase pointer position then write
* IN : data to push
* OUT : 1 on error, otherwise 0
**************************************************/
int fifo_push(fifoType* data)
{

	if(fifo_isFull()){
		printf("FIFO is full\n");
		return 1;
	}

	/* Write */
	fifo.msgList[fifo.head] = *data;
	
	/* Increase */
	fifo.head = (fifo.head+1) % fifo.size;

	/* Read is now possible */
	if(fifo.tail == -1)
		fifo.tail = 0;

	fifo.nbData++;
	
	return 0;
}


/**************************************************
* NAME : fifo_forcePush
* BRIEF : Push data weither FIFO is FULL, meaning popping data if necessary
* IN : data to push
* OUT : 1 on error, otherwise 0
**************************************************/
int fifo_forcePush(fifoType* data)
{
	fifoType lostData;
	
	while(fifo_push(data)){
		fifo_pop(&lostData);
	}

	return 0;
}


/**************************************************
* NAME : fifo_checkData
* BRIEF : read data at index. Read the increase pointer position
* IN : pointer to the data to read
* OUT : 1 on error, otherwise 0
**************************************************/
int fifo_checkData(int index, fifoType* data)
{
	if(fifo_isEmpty()){
		printf("FIFO is empty\n");
		return 1;
	}
	/* Check boundaries */
	if((index > (fifo.size -1))||(index<0)){
		printf("index invalid : out of boudaries\n");
		return 1;
	}
	
	/* Check valid data (not already poped out)*/
	if((index <= fifo.tail)&&(index>fifo.head))
		printf("Data might be invalid\n");

	*data = fifo.msgList[index];
	
	return 0;
}

/**************************************************
* NAME : fifo_pop
* BRIEF : pop out data from the fifo. Pointer(tail) stays on the last popped index
* IN : pointer to the data to read
*  OUT : 1 on error, otherwise 0
**************************************************/
int fifo_pop(fifoType* data)
{
	if(fifo_isEmpty()){
		printf("FIFO is empty\n");
		return 1;
	}

	/* Read */
	*data = fifo.msgList[fifo.tail];
	/* Wrap / increase pointer */
	fifo.tail = (fifo.tail+1) % fifo.size;
	
	fifo.nbData--;
	
	return 0;
}

/**************************************************
* NAME : fifo_isEmpty
* BRIEF : check if FIFO is empty
* IN : void
* OUT : 1 is empty, 0 otherwise
**************************************************/
int fifo_isEmpty(void)
{
	if((fifo.head == fifo.tail) || (fifo.tail == -1 ))
		return true;
	else
		return false;
}

/**************************************************
* NAME : fifo_isFull
* BRIEF : check if FIFO is full
* IN : void
* OUT : 1 is full, 0 otherwise
**************************************************/
int fifo_isFull(void)
{
	int nextHead = (fifo.head+1) % fifo.size;

	if(nextHead == fifo.tail)
		return true;
	else
		return false;

}


/**************************************************
* NAME : menu
* BRIEF : Display a control menu allowing test
* IN :
* OUT :
**************************************************/
void menu(void)
{
	printf("MENU\n");
	printf("Quit 		: 0\n");
	printf("Menu Display 	: 1\n");
	printf("Push 		: 2\n");
	printf("Pop 		: 3\n");
	printf("Dsp FIFO	: 4\n");
	printf("Dsp FIFO Stat	: 5\n");
}



/**************************************************
* NAME : 
* BRIEF :
* IN :
* OUT :
**************************************************/
int main(void)
{
	int loop=true;
	int cmd, ckloop;
	unsigned char data;

	menu();

	init(0);

	while(loop){
		data =-1;
		printf("Enter Command:\n");
		scanf("%i",&cmd);
		
		switch(cmd){
		case 0:
			loop=false;
			break;
		
		case 1:
			menu();
			break;
		case 2:
			printf("Enter Data: ");
			scanf("%hhu",&data);
			fifo_push(&data);
			break;
		case 3:
			if(fifo_pop(&data))
				break;
			printf("Pop data = %d \n",data);
			break;
		case 4:
			for(ckloop = 0; ckloop < fifo.size; ckloop++){
				if(fifo_checkData(ckloop,&data))
					break;
				printf("FIFO[%d] = %d \n",ckloop, data);
				
			}
			break;
		case 5:
			printf("-----\nFIFO Stat:\n");
			printf("Fifo.head 	= %d \n",fifo.head);
			printf("Fifo.tail 	= %d \n",fifo.tail);
			printf("Fifo.size 	= %d \n",fifo.size);
			printf("Fifo.nbData 	= %d \n",fifo.nbData);
			printf("Fifo is full 	= %d \n",fifo_isFull());
			printf("Fifo is empty 	= %d \n------\n",fifo_isEmpty());
			break;
		}
	
	}
	return 0;
}

