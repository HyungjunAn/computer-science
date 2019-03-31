#ifndef _GPIO_NUM_H_
#define _GPIO_NUM_H_

/*
	wiringPiSetup();
	mcp3422Setup(400, 0x6a, 0, 0);

	pinMode(SW, INPUT);
	pinMode(LED, PWM_OUTPUT);
	pinMode(BLUE_LED, OUTPUT);        

	softPwmCreate(BLUE_LED, 0, 1024);

	softServoSetup(SERVO, -1, -1, -1, -1, -1, -1, -1);

	analogRead(NUMBER);
	digitalWrite(led, n); 		// n = HIGH, LOW
	softServoSetup(SERVO, -1, -1, -1, -1, -1, -1, -1);
	softServoWrite(SERVO, n);   // -250 <= n <= 1250
	pwmWrite(LED, n); 			// n <= [0, 1023]
	softPwmWrite(BLUE_LED, n); 		// n <= [0, range]
*/

#define CDS 400
#define TMP36 401
#define VR 403
#define SERVO 25

const int LED[] = {27, 24, 28, 29};
const int LED_NUM = sizeof(LED) / sizeof(LED[0]);

const int RGB[] = {23, 26, 22};
const int RGB_NUM = sizeof(RGB) / sizeof(RGB[0]);

const int SW[] = {4, 5};
const int SW_NUM = sizeof(SW) / sizeof(SW[0]);

const int STEP_PIN[] = {27, 24, 28, 29};
const int STEP_PIN_NUM = sizeof(STEP_PIN) / sizeof(STEP_PIN[0]);

const int STEP_SEQ[][4] = {
	{1,0,0,1},
	{1,0,0,0},
	{1,1,0,0},
	{0,1,0,0},
	{0,1,1,0},
	{0,0,1,0},
	{0,0,1,1},
	{0,0,0,1}
};
const int STEP_SEQ_NUM = sizeof(STEP_SEQ) / sizeof(STEP_SEQ[0]);

const int S7_PIN[] = {1, 2, 3};
const int S7_PIN_NUM = sizeof(S7_PIN) / sizeof(S7_PIN[0]);

const int S7_S[8]    = { 11, 10, 13, 12, 14, 15, 16, 0 };
const int S7_S_NUM = sizeof(S7_S) / sizeof(S7_S[0]);

const int S7_NUMARR[10] = {
	0xFC,
	0x60,
	0xDA,
	0xF2,
	0x66,
	0xB6,
	0xBE,
	0xE0,
	0xFE,
	0xF6,
};

#endif
