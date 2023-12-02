TITLE = listmv
CC = clang
VER = c99

# this is for my personal debugging
test:
	$(CC) tests/list.c -I . -o temp/list -std=$(VER)
