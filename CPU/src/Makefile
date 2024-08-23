CC=gcc

CFLAGS = -Iinstructions -I. -g

SRCS = cpu.c instructions/instructions.c 

EXEC=cpu

all:
	$(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) $(SRCS) -o $@

clean:
	rm -f $(EXEC)

# Phony targets to avoid conflict with files of the same name
.PHONY: all clean