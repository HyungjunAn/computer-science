project: hello.out trans.out snake.out

hello.out: hello.c ssd1306_i2c.c ssd1306_i2c.h
	gcc hello.c ssd1306_i2c.c -o $@ -lwiringPi

snake.out: snake.c ssd1306_i2c.c ssd1306_i2c.h
	gcc snake.c ssd1306_i2c.c -o $@ -lwiringPi

trans.out: trans.c
	gcc trans.c -o $@
