CC=gcc

SRC_DIR_CPU = /home/jack/Desktop/Jack-OS/CPU/src
SRC_DIR_SCHEDULE = /home/jack/Desktop/Jack-OS/Kernel/Scheduling

CFLAGS = -I. -I${SRC_DIR_CPU} -I${SRC_DIR_CPU}/instructions -I${SRC_DIR_SCHEDULE} -g

SRCS = jmemory.c  ${SRC_DIR_CPU}/cpu.c ${SRC_DIR_CPU}/instructions/instructions.c ${SRC_DIR_SCHEDULE}/schedule.c

EXEC=mem

all:
	$(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) $(SRCS) -o $@

clean:
	rm -f $(EXEC)

# Phony targets to avoid conflict with files of the same name
.PHONY: all clean