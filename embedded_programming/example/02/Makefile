CFLAGS = -lwiringPi

project: main.out

main.out: %.o main.o ssd1306_i2c.o ssd1306_i2c.h
	gcc main.o ssd1306_i2c.o -o $@ $(CFLAGS)

%.o: %.c
	gcc -c -o $@ $<
