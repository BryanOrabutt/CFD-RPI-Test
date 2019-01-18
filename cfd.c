#include <stdio.h>
#include <wiringPi.h>
#include <string.h>

/* Chip defines */
#define DATA_BITS	8
#define MODE_BITS	4
#define ADDR_BITS	4


/* Pin accessors */
const unsigned char DATA[8] = {2,3,4,17,27,22,10,9}; //data bus -- used to load configuration registers
const unsigned char ADDR[4] = {2,3,4,17}; //address bus -- just an alias of the upper nibble of the data bus
const unsigned char MODE[4] = {27,22,10,9}; //mode bus -- just an alias of the lower nibble of the data bus
const unsigned char NEG_POL = 11; //negative polarity enable -- POS,NEG = 0,1
const unsigned char BUS_DIR = 5; //bidirectional bus control -- IN,OUT = 1,0
const unsigned char STB = 6; //data/address strobe -- addr/mode latched on rising edge, data latched on falling edge
const unsigned char GEN = 13; //global enable -- OUTPUT,NO_OUTPUT = 1,0
const unsigned char EXT_AGND = 19; //external AGND enable -- INTERNAL,EXTERNAL = 0,1

unsigned int iter; //loop variable
unsigned char STB_STATE = 0; //flag to keep track of state of STB

void d_latch(char bits);
void am_latch(char bits);
void clear_all(void);
void set_ctl_pin(char pin, char state); //helper function for GUI. Just does a digitalWrite
void read_file(FILE* fid);


void setup(void)
{
	pinMode(BUS_DIR, OUTPUT);
	pinMode(STB, OUTPUT);
	pinMode(GEN, OUTPUT);
	pinMode(EXT_AGND, OUTPUT);
	pinMode(NEG_POL, OUTPUT);
	
	for(iter = 0; iter < DATA_BITS; iter++)
	{
		pinMode(DATA[iter], OUTPUT);
	}

	digitalWrite(BUS_DIR, 1); //keep bidrectional bus as input
}

int main(void)
{
	char s[4];
	strncpy(s, "Test", 4);
	printf("%s\n", s);

	if(wiringPiSetupGpio() == -1)
		return 1;

	setup();

	for(;;)
	{
		digitalWrite(0, 1);
		delay(500);
		digitalWrite(0, 0);
		delay(500);
	}

	return 0;
}


void d_latch(char bits)
{
	//todo: latch data on falling edge of stb
}

void am_latch(char bits)
{
	//todo: latch address and mode on rising edge of stb
}

void clear_all(void)
{
	//todo: clear all registers to 0
}

void set_ctl_pin(char pin, char state)
{
	digitalWrite(pin, state);
}

void read_files(FILE* fid)
{
	//todo: read csv file containing addr/mode,data and latch them appropriately.
}
