#include "fifo.h"


struct s_fifo fifo;

void init(int size)
{
	fifo.size = FIFO_SIZE;
	fifo.tail = FIFO_SIZE;
	fifo.head = 0;
	memset(&fifo.msgList, 0, sizeof(fifoType)*FIFO_SIZE);
}

int push(fifoType* data)
{

	if(isFull()){
		printf("FIFO is full\n");
		return 0;
	}

	fifo.msgList[++fifo.head] = *data;

	/* Wrap */
	if(fifo.head == fifo.size)
		fifo.head = 0;

	/* Read is now possible */
	if(fifo.tail == FIFO_SIZE)
		fifo.tail =0;
}

int checkData(int index, fifoType* data)
{
	if(isEmpty()){
		printf("FIFO is empty\n");
		return 0;
	}
	if(index > (fifo.size -1)){
		printf("index overflow\n");
		return;
	}

	*data = fifo.msgList[index];
	
	return 1;
}

void pop(fifoType* data)
{
	if(isEmpty()){
		printf("FIFO is empty\n");
		return;
	}

	/* Wrap */
	if(fifo.tail+1 == fifo.size)
		fifo.tail = 0;
	else
		fifo.tail++;

	*data = fifo.msgList[fifo.tail];
}

int isEmpty(void)
{
	if((fifo.head == fifo.tail) || (fifo.tail == FIFO_SIZE) )
		return true;
	else
		return false;
}

int isFull(void)
{
	int nextHead = fifo.head+1;
	if(nextHead >= fifo.size)
		nextHead = 0;

	if(nextHead == fifo.tail)
		return true;
	else
		return false;

/* other solution to code it :
	if(((fifo.head+1) % fifo.size) == fifo.tail)
		return true;
	else
		return false;
*/
}



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


int main(void)
{
	int loop=true;
	int cmd, ckloop;
	char data;
	
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
			scanf("%i",&data);
			push(&data);
			break;
		case 3:
			pop(&data);
			printf("Pop data = %d \n",data);
			break;
		case 4:
			for(ckloop = 0; ckloop < fifo.size; ckloop++){
				if(checkData(ckloop,&data))
					printf("FIFO[%d] = %d \n",ckloop, data);
			}
			break;
		case 5:
			printf("FIFO Stat:\n");
			printf("Fifo.head 	= %d \n",fifo.head);
			printf("Fifo.tail 	= %d \n",fifo.tail);
			printf("Fifo.size 	= %d \n",fifo.size);
			printf("Fifo is full 	= %d \n",isFull());
			printf("Fifo is empty 	= %d \n",isEmpty());
			break;
		}
	
	}

}

