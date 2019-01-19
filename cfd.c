#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <string.h>
#include "cfd.h"

/* Pin accessors */
const unsigned char DATA[8] = {2,3,4,17,27,22,10,9}; //data bus -- used to load configuration registers
const unsigned char ADDR[4] = {2,3,4,17}; //address bus -- just an alias of the upper nibble of the data bus
const unsigned char MODE[4] = {27,22,10,9}; //mode bus -- just an alias of the lower nibble of the data bus
const unsigned char NEG_POL = 11; //negative polarity enable -- POS,NEG = 0,1
const unsigned char BUS_DIR = 5; //bidirectional bus control -- IN,OUT = 1,0
const unsigned char STB = 6; //data/address strobe -- addr/mode latched on rising edge, data latched on falling edge
const unsigned char GEN = 13; //global enable -- OUTPUT,NO_OUTPUT = 1,0
const unsigned char EXT_AGND = 19; //external AGND enable -- INTERNAL,EXTERNAL = 0,1
const unsigned char RST_L = 26; //low active reset -- ensures one-shot works properly.

int iter; //loop variable
unsigned char STB_STATE = 0; //flag to keep track of state of STB

void d_latch(char bits);
void am_latch(char bits);
void clear_all(void);
void set_ctl_pin(char pin, char state); //helper function for GUI. Just does a digitalWrite
void read_file(char* file_name);


void setup(void)
{
	pinMode(BUS_DIR, OUTPUT);
	pinMode(STB, OUTPUT);
	pinMode(GEN, OUTPUT);
	pinMode(EXT_AGND, OUTPUT);
	pinMode(NEG_POL, OUTPUT);
	pinMode(RST_L, OUTPUT);
	
	for(iter = 0; iter < DATA_BITS; iter++)
	{
		pinMode(DATA[iter], OUTPUT);
	}

	digitalWrite(BUS_DIR, 1); //keep bidrectional bus as input
	digitalWrite(RST_L, 0); //reset one-shot
	delay(1); //wait 1 ms
	digitalWrite(RST_L, 1); //bring one-shot out of reset so output can be generated.
}

int main(void)
{
	if(wiringPiSetupGpio() == -1)
		return 1;

	setup();

	printf("CFD test system initialized\n");
	
	/* Test control signals */
	printf("Setting NEG_POL to 0\n");
	set_ctl_pin(NEG_POL, 0);
	printf("Setting GEN to 1\n");
	set_ctl_pin(GEN, 1);
	printf("Setting EXT_AGND to 1\n");
	set_ctl_pin(EXT_AGND, 1);
	
	/* Load some data using GMODE */
	char bits = 0;
	printf("Setting address and mode to %u\n", (GMODE | COMMON | DAC_MODE));
	bits = COMMON | GMODE | DAC_MODE;
	am_latch(bits);
	
	printf("Waiting to allow measurement....\n");
	delay(300000);
	bits = 0x2f; //DAC value used in simulation test benches.
	printf("Loading all channel DACs with 0x2f\n");
	d_latch(bits);	

	printf("Waiting to allow measurement....\n");
	delay(300000); //give time to probe signals
	
	return 0;	
}

/* Data latch -- Data is latched on the falling edge of STB using the shared ADDRDAT bus.
 * char bits: an 8-bit number representing the data payload.
 */
void d_latch(char bits)
{
	if(STB_STATE == 0)
	{
		printf("Data can only be latched on falling edge. Please latch address/mode first!");
		exit(1);
	}

	for(iter = DATA_BITS-1; iter > 0; iter--)
	{
		digitalWrite(DATA[iter], bits & 1);
		bits = bits >> 1;
	}

	delayMicroseconds(1); //ensures data bus meets setup and hold times
	digitalWrite(STB, 0); //bring STB low to latch data
	STB_STATE = 0;
}

/* Address & mode latch -- Address & mode are latched on the rising edge of STB using the shared ADDRDAT bus.
 * char bits: an 8-bit number representing address and mode. The upper nibble of the byte will be the address
 * while the lower niblle of the byte is the mode. (addr: selects channel to load data to, mode: selects 
 * register in the channel to load data to, common channel address = 0). MSB of mode is GMODE which causes
 * address to be ignored, selecting ALL registers of a given mode (useful for loading channel DACs).
 */
void am_latch(char bits)
{
	if(STB_STATE == 1)
	{
		printf("Address & Mode can only be latched on the rising edge. Please latch data first!");
		exit(1);
	}

	for(iter = MODE_BITS-1; iter > 0; iter--)
	{
		digitalWrite(MODE[iter], bits & 1);
		bits = bits >> 1;
	}

	for(iter = ADDR_BITS-1; iter > 0; iter--)
	{
		digitalWrite(ADDR[iter], bits & 1);
		bits = bits >> 1;
	}

	delayMicroseconds(1); //ensures address/mode meet setup and hold times
	digitalWrite(STB, 1); //bring STB high to latch address and mode
	STB_STATE = 1;
}

void clear_all(void)
{
	//todo: clear all registers to 0
}

/* Helpher function for python GUI to change control pins
 * char pin: the GPIO pin number whose state will be changed.
 * char state: the state the pin will be changed to.
 */
void set_ctl_pin(char pin, char state)
{
	switch(pin)
	{
		case 11:
		case 5:
		case 16:
		case 13:
		case 19:
		case 26:
			break;
		default:
			printf("Pin not valid. Please only provide a pin mapped to a control signal\n");
			exit(1);
			break;

	}

	if(state > 1 || state < 0)
	{
		printf("State must be 0 or 1!\n");
		exit(1);
	}

	digitalWrite(pin, state);
}

void read_files(char* file_name)
{
	//todo: read csv file containing addr/mode,data and latch them appropriately.
}
