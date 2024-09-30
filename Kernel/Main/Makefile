CC=gcc

PROJ_DIR = /home/jack/Desktop/Jack-OS

SRC_DIR_CPU = ${PROJ_DIR}/CPU/src
SRC_DIR_SCHEDULE = ${PROJ_DIR}/Kernel/Scheduling/src
SRC_DIR_MEM = ${PROJ_DIR}/Kernel/Memory/src
SRC_DIR_CALLS = ${PROJ_DIR}/Kernel/syscalls/src
SRC_DIR_GLOBAL = ${PROJ_DIR}/Kernel/Globals
SRC_DIR_THREADS = ${PROJ_DIR}/Kernel/Threads
SRC_DIR_JSHELL = ${PROJ_DIR}/J_Shell/src

CFLAGS = -I. -I${SRC_DIR_CPU} -I${SRC_DIR_CPU}/instructions -I${SRC_DIR_MEM} -I${SRC_DIR_CALLS} -I${SRC_DIR_SCHEDULE} -I${SRC_DIR_GLOBAL} -I${SRC_DIR_THREADS} -I${SRC_DIR_JSHELL} -g

SRCS = $(shell find $(PROJ_DIR) -name '*.c')

EXEC=kernel

all:
	$(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) $(SRCS) -o $@

clean:
	rm -f $(EXEC)

# Phony targets to avoid conflict with files of the same name
.PHONY: all clean