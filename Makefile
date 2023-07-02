CFLAGS=-Wall
LDFLAGS=-llgpio

all: onkyo-send-command

onkyo-send-command: common.o

clean:
	rm -f *.o onkyo-send-command
