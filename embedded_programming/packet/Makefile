
softServo_o = /root/wiringPi/wiringPi/softServo.o

all: server client

server:			server.o readn.o
	gcc -o $@ server.o readn.o $(softServo_o) -lwiringPi -lpthread
client:			client.o
	gcc -o $@ client.o -lwiringPi
server.o:		server.c  gpio_num.h
	gcc -c server.c -o $@
readn.o:		readn.c 
	gcc -c readn.c -o $@
client.o:		client.c gpio_num.h
	gcc -c client.c -o $@
clean:
	rm *.o client server
