TITLE = listmv
CC = gcc

build:
	gcc listmv.c -c

install: # linux-only
	gcc 