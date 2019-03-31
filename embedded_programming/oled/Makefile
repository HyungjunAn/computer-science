SSD_PATH = /root/lcd_test
SSD_O = $(SSD_PATH)/ssd1306_i2c.o
CFLAGS = -lwiringPi -I$(SSD_PATH)

project: hello.out trans.out snake.out

hello.out: hello.o $(SSD_O)
	gcc $^ -o $@ $(CFLAGS)

snake.out: snake.o $(SSD_O)
	gcc $^ -o $@ $(CFLAGS)

trans.out: trans.o $(SSD_O)
	gcc $^ -o $@ $(CFLAGS)

%.o: %.c %.h
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm *.o *.out
