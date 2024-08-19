CC=gcc

CFLAGS = -Iinstructions -I../../libraries/jacklib -I. -g

SRCS = cpu.c instructions/instructions.c ../../libraries/jacklib/jacklib.c

EXEC=cpu

all:
	$(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) $(SRCS) -o $@

clean:
	rm -f $(EXEC)

# Phony targets to avoid conflict with files of the same name
.PHONY: all clean