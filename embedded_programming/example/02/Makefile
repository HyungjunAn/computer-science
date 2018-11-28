SSD_PATH = /root/lcd_test
SSD_O = $(SSD_PATH)/ssd1306_i2c.o
CFLAGS = -lwiringPi -I$(SSD_PATH)

project: main.out

main.out: main.o $(SSD_O)
	gcc $^ -o $@ $(CFLAGS)

%.o: %.c
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm *.o *.out
