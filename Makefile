CFLAGS=-Wall
LDFLAGS=-llgpio

all: onkyo-ri-send-command

onkyo-ri-send-command: common.o

clean:
	rm -f *.o onkyo-ri-send-command
