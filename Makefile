################################################################################
##
##
##
##
##
################################################################################
RED=\033[0;31m
NC=\033[0;0m

CC = gcc
CFLAGS = -I. -Wall
LDFLAGS =

SRC = fifo.c
HDR = $(SRC:.c=.h)
OBJ = $(SRC:.c=.o)
DEPS = 

OUT = fifo

all:$(OUT)
	@echo -e "${RED}Make All Done ${NC}"

$(OUT):$(OBJ)
	@echo -e "${RED}Link Object ${NC}"
	$(CC) $? $(LDFLAGS) -o $@
	

$(OBJ):$(SRC) $(DEPS) $(HDR)
	@echo -e "${RED}Compile Object ${NC}"
	$(CC) -c $(CFLAGS) $(SRC)
	
clean:
	@echo "${RED}Make Clean - Remove all Object file (*.o)${NC}"
	rm -f *.o

distclean:
	@echo "${RED}Make DistClean ${NC}"
	rm -f ${OUT}
