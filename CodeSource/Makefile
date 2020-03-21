#Makefile 
TARGETS = main

CROSS_TOOL = 
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=c99 -Werror -pthread -DTEST --debug

all: clean $(TARGETS)

$(TARGETS):
	$(CC_C) $(CFLAGS) $@.c -lm -o $@

clean:
	rm $(TARGETS)