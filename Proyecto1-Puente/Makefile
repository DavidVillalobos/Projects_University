#Makefile for building demo applications.
# by David Villalobos

#Edit this file to compile extra C files into their own programs
TARGETS= main

CROSS_TOOL = 
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=c99 -Werror -pthread

all: clean $(TARGETS)

$(TARGETS):
	$(CC_C) $(CFLAGS) $@.c -lm -o $@

clean:
	rm -f $(TARGETS)