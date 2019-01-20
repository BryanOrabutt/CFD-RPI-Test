#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <string.h>
#include <unistd.h>
#include "cfd.h"

const char USAGE[] ="cfd [-f file][-a address/mode][-d data][-p pin -s state][-C]\n\nDescription: Used to configure the CFD16C IC from a raspberry pi.\n\nOptions:\n\t-f file\n\t\tReads the specified file as a configuration file for the CFD16C. The file format is similar to csv using comma seperated tokens.\n\t\tUp to three tokens may be specified per line. See example config file in the config directory.\n\t-a address/mode\n\t\tAllows an 8 bit number (i.e. char) to be specified to use as the address/mode for the chip and latches the address/mode.\n\t-d data\n\t\tAllows an 8 bit number (i.e. char) to be specified to use as the data for the chip and latches the data\n\t-p pin -s state\n\t\tAllows a pin and state to be specified to change a specific control signal to the CFD16C.\n\t-C\n\n\t\tClears all of the registers to a data value of\n";

/* Pin accessors */
const unsigned char DATA[8] = {21,22,23,24,25,27,28,29}; //data bus -- used to load configuration registers
const unsigned char ADDR[4] = {21,22,23,24}; //address bus -- just an alias of the upper nibble of the data bus
const unsigned char MODE[4] = {25,27,28,29}; //mode bus -- just an alias of the lower nibble of the data bus
const unsigned char NEG_POL = 11; //negative polarity enable -- POS,NEG = 0,1
const unsigned char BUS_DIR = 5; //bidirectional bus control -- IN,OUT = 1,0
const unsigned char STB = 6; //data/address strobe -- addr/mode latched on rising edge, data latched on falling edge
const unsigned char GEN = 13; //global enable -- OUTPUT,NO_OUTPUT = 1,0
const unsigned char EXT_AGND = 4; //external AGND enable -- INTERNAL,EXTERNAL = 0,1
const unsigned char RST_L = 26; //low active reset -- ensures one-shot works properly.

int iter; //loop variable
unsigned char STB_STATE = 0; //flag to keep track of state of STB

void d_latch(char bits);
void am_latch(char bits);
void clear_all(void);
void set_ctl_pin(char pin, char state); //helper function for GUI. Just does a digitalWrite
void read_file(char* file_name);
const char* get_tok(char* line, int num); //gets a token number from a given line.

/* Initialized the GPIO ports and sets initial states */
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

int main(int argc, char** argv)
{
	int c;
	char pin, state, bits;
	char* fn;

	if(wiringPiSetupGpio() == -1)
		exit(1);

	setup();

	printf("CFD test system initialized\n");
	
	if(argc < 2)
	{
		printf("%s", USAGE);
		exit(1);
	}

	while((c = getopt(argc, argv, "f:a:d:p:s:C")) != -1)
	{
		switch(c)
		{
			case 'f':
				fn = optarg;
				read_file(fn);
				break;
			case 'a':
				am_latch(atoi(optarg));
				break;
			case 'd':
				d_latch(atoi(optarg));
				break;
			case 'p':
				pin = atoi(optarg);
				break;
			case 's':
				state = atoi(optarg);
				break;
			case 'C':
				bits = GMODE | NOWLIN_MODE;
				am_latch(bits);
				d_latch(0);
				bits = GMODE | ONESHOT_MODE;
				am_latch(bits);
				d_latch(0);
				bits = GMODE | DAC_MODE;
				am_latch(bits);
				d_latch(0);
				bits = LOCKOUT_MODE | GMODE;
				am_latch(bits);
				d_latch(0);
				break;
			default:
				printf("%s", USAGE);
		}
	}

	return(0);
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
 * while the lower nibble of the byte is the mode. (addr: selects channel to load data to, mode: selects 
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

/* Helper function for python GUI to change control pins
 * char pin: the GPIO pin number whose state will be changed.
 * char state: the state the pin will be changed to.
 */
void set_ctl_pin(char pin, char state)
{
	switch(pin)
	{
		/* Valid control pin will just break and continue */
		case 11:
		case 5:
		case 6:
		case 13:
		case 4:
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

/* Read a file to configure the CFD16C. File format is similar to CSV with certain expected tokens.
 * char* file_name: The name of the file to read from.
 *
 * token 1: d -- indicates the next token is 8 ASCII characters representing a bit string for the 
 *	    shared data bus.
 * 	    am -- indicates the next token is 8 ASCII characters representing the address and mode
 *	    values for the shared data bus.
 *	    ctl -- indicates the next token is the control signal pin to change, with a third token
 *	    representing the state to change the pin to.
 *
 * token 2: depends on token 1. If token 1 was "d" or "am" then this token should be an ASCII bit string.
 *	    eg. 11011000
 *	    If token 1 was "ctl" then this token should be a valid control signal pin.
 *	    eg. 11 -- (NEG_POL)
 *
 * token 3: Only used if token 1 was "ctl". This should be the to which you wish to change the state 
 *	    of the control signal pin indicated by token 2. Must be 0 or 1.
 */
void read_file(char* file_name)
{
	ssize_t bytes;
	FILE* fid = fopen(file_name, "r");
	char* line = NULL;	
	size_t len = 0;

	if(!fid)
	{
		printf("Could not open file. Please make sure file exists!\n");
		exit(2);
	}

	/* Read the file line by line and parse out the two csv tokens */
	while((bytes = getline(&line, &len, fid)) != -1)
	{
		char* s = strdup(line); //create copy of line since strtok() will clobber the input string
		const char* t = get_tok(s, 1);

		if(strncmp(t, "am", 8) == 0) //am denotes address/mode bus values
		{
			char* tmp = strdup(line); //since s got clobbered copy line into tmp
			const char* t2 = get_tok(tmp, 2); //get the token
			char num = 0;
			for(iter = 0; iter < DATA_BITS; iter++)
			{
				num |= (t2[iter]-48) & 1;
				num = num << 1;
			}
		
			am_latch(num);
			free(tmp);
			free((char*)t2);
		}
		else if(strncmp(t, "d", 8) == 0)
		{
			char* tmp = strdup(line);
			const char* t2 = get_tok(tmp, 2);
			char num = 0;
			for(iter = 0; iter < DATA_BITS; iter++)
			{
				num |= (t2[iter]-48) & 1;
				num = num << 1;
			}
		
			d_latch(num);
			free(tmp);
			free((char*)t2);
		}
		else if(strncmp(t, "ctl", 8) == 0)
		{
			char* tmp = strdup(line);
			char pin = atoi(get_tok(tmp, 2));
			free(tmp); //clear memory pointed at by tmp to avoid mem leaks.
			tmp = strdup(line); //recopy line to do another token search
			char state = atoi(get_tok(tmp, 3));
			set_ctl_pin(pin, state);
			free(tmp);
		}
		else
		{
			printf("Invalid token: %s\n", s);
			free(line);
			fclose(fid);
			free(s);
			exit(1);	
		}
	
		free(s);		
	}

	free(line);
	fclose(fid);	
}


const char* get_tok(char* line, int num)
{
	const char* tok;

	for(tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n"))
	{
		num--;
		if(!num)
		{
			return tok;
		}
	}

	return NULL;
}
