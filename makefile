CC=gcc
OBJS=body.o list.o
EXEC=danielCity
DEBUG=#for debugging delete the line from the = to here -g
CFLAGS=-std=c99 Wall- Werror- $(DEBUG)
$(EXEC) : $(OBJS)
	$(CC)  $(CFLAGS) $(OBJS) -o $@

body.o: main_test_block.c List.h
list.o: List.c List.h