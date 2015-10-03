/*
 * righop.c
 * 
 * A crappy program to jump around an array of frequencies every second
 * using a Ham Radio transceiver with CAT/CI-V control.
 * 
 * Uses computer clock with tight time syncrhonisation to NTP
 * 
 * Users must have synced clocks with NTP and use the same SEED and 
 * 
 * Copyright 2015 George Smart M1GEO
 * 	Email: george@m1geo.com
 * 	Web: http://www.george-smart.co.uk
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

// hopping frequencies in Hz - must be the same for all users
long unsigned int hopping_frequencies[] = {431000000, 431012500, 431025000, 431037500, 431050000, 431062500, 431075000, 431087500, 431100000, 431112500, 431125000, 431137500, 431150000, 431162500, 431175000, 431187500, 431200000, 431212500, 431225000, 431237500, 431250000, 431262500, 431275000, 431287500, 431300000, 431312500, 431325000, 431337500, 431350000, 431362500, 431375000, 431387500, 431400000, 431412500, 431425000, 431437500, 431450000, 431462500, 431475000, 431487500, 431500000, 431512500, 431525000, 431537500, 431550000, 431562500, 431575000, 431587500, 431600000, 431612500, 431625000, 431637500, 431650000, 431662500, 431675000, 431687500, 431700000, 431712500, 431725000, 431737500, 431750000, 431762500, 431775000, 431787500, 431800000, 431812500, 431825000, 431837500, 431850000, 431862500, 431875000, 431887500, 431900000, 431912500, 431925000, 431937500, 431950000, 431962500, 431975000, 431987500, 432000000, 432012500, 432025000, 432037500, 432050000, 432062500, 432075000, 432087500, 432100000, 432112500, 432125000, 432137500, 432150000, 432162500, 432175000, 432187500, 432200000, 432212500, 432225000, 432237500, 432250000, 432262500, 432275000, 432287500, 432300000, 432312500, 432325000, 432337500, 432350000, 432362500, 432375000, 432387500, 432400000, 432412500, 432425000, 432437500, 432450000, 432462500, 432475000, 432487500, 432500000, 432512500, 432525000, 432537500, 432550000, 432562500, 432575000, 432587500, 432600000, 432612500, 432625000, 432637500, 432650000, 432662500, 432675000, 432687500, 432700000, 432712500, 432725000, 432737500, 432750000, 432762500, 432775000, 432787500, 432800000, 432812500, 432825000, 432837500, 432850000, 432862500, 432875000, 432887500, 432900000, 432912500, 432925000, 432937500, 432950000, 432962500, 432975000, 432987500, 435000000, 435012500, 435025000, 435037500, 435050000, 435062500, 435075000, 435087500, 435100000, 435112500, 435125000, 435137500, 435150000, 435162500, 435175000, 435187500, 435200000, 435212500, 435225000, 435237500, 435250000, 435262500, 435275000, 435287500, 435300000, 435312500, 435325000, 435337500, 435350000, 435362500, 435375000, 435387500, 435400000, 435412500, 435425000, 435437500, 435450000, 435462500, 435475000, 435487500, 435500000, 435512500, 435525000, 435537500, 435550000, 435562500, 435575000, 435587500, 435600000, 435612500, 435625000, 435637500, 435650000, 435662500, 435675000, 435687500, 435700000, 435712500, 435725000, 435737500, 435750000, 435762500, 435775000, 435787500, 435800000, 435812500, 435825000, 435837500, 435850000, 435862500, 435875000, 435887500, 435900000, 435912500, 435925000, 435937500, 435950000, 435962500, 435975000, 435987500, 436000000, 436012500, 436025000, 436037500, 436050000, 436062500, 436075000, 436087500, 436100000, 436112500, 436125000, 436137500, 436150000, 436162500, 436175000, 436187500, 436200000, 436212500, 436225000, 436237500, 436250000, 436262500, 436275000, 436287500, 436300000, 436312500, 436325000, 436337500, 436350000, 436362500, 436375000, 436387500, 436400000, 436412500, 436425000, 436437500, 436450000, 436462500, 436475000, 436487500, 436500000, 436512500, 436525000, 436537500, 436550000, 436562500, 436575000, 436587500, 436600000, 436612500, 436625000, 436637500, 436650000, 436662500, 436675000, 436687500, 436700000, 436712500, 436725000, 436737500, 436750000, 436762500, 436775000, 436787500, 436800000, 436812500, 436825000, 436837500, 436850000, 436862500, 436875000, 436887500, 436900000, 436912500, 436925000, 436937500, 436950000, 436962500, 436975000, 436987500, 437000000, 437012500, 437025000, 437037500, 437050000, 437062500, 437075000, 437087500, 437100000, 437112500, 437125000, 437137500, 437150000, 437162500, 437175000, 437187500, 437200000, 437212500, 437225000, 437237500, 437250000, 437262500, 437275000, 437287500, 437300000, 437312500, 437325000, 437337500, 437350000, 437362500, 437375000, 437387500, 437400000, 437412500, 437425000, 437437500, 437450000, 437462500, 437475000, 437487500, 437500000, 437512500, 437525000, 437537500, 437550000, 437562500, 437575000, 437587500, 437600000, 437612500, 437625000, 437637500, 437650000, 437662500, 437675000, 437687500, 437700000, 437712500, 437725000, 437737500, 437750000, 437762500, 437775000, 437787500, 437800000, 437812500, 437825000, 437837500, 437850000, 437862500, 437875000, 437887500, 437900000, 437912500, 437925000, 437937500, 437950000, 437962500, 437975000, 437987500, 438000000, 438012500, 438025000, 438037500, 438050000, 438062500, 438075000, 438087500, 438100000, 438112500, 438125000, 438137500, 438150000, 438162500, 438175000, 438187500, 438200000, 438212500, 438225000, 438237500, 438250000, 438262500, 438275000, 438287500, 438300000, 438312500, 438325000, 438337500, 438350000, 438362500, 438375000, 438387500, 438400000, 438412500, 438425000, 438437500, 438450000, 438462500, 438475000, 438487500, 438500000, 438512500, 438525000, 438537500, 438550000, 438562500, 438575000, 438587500, 438600000, 438612500, 438625000, 438637500, 438650000, 438662500, 438675000, 438687500, 438700000, 438712500, 438725000, 438737500, 438750000, 438762500, 438775000, 438787500, 438800000, 438812500, 438825000, 438837500, 438850000, 438862500, 438875000, 438887500, 438900000, 438912500, 438925000, 438937500, 438950000, 438962500, 438975000, 438987500};
//long unsigned int hopping_frequencies[] = { 29100000,    29110000,    29120000,    29130000,    29140000,    29150000,    29160000,    29170000};

// hopping pattern
unsigned int hopping_pattern[60] = {439, 79, 101, 262, 74, 280, 299, 105, 11, 31, 47, 20, 227, 344, 374, 193, 45, 330, 302, 18, 137, 433, 458, 40, 188, 273, 46, 53, 59, 462, 201, 230, 99, 309, 342, 476, 68, 290, 371, 193, 285, 182, 461, 442, 115, 245, 291, 349, 188, 62, 297, 159, 76, 14, 295, 162, 125, 435, 70, 37};

// Icom CI-V Addresses - rigaddress is copied from argv[2] using my ropey str2hex()
unsigned short rigaddress = 0x88; // in HEX (radio CI-V address, IC7100=88h)
unsigned short computerad = 0xE0; // in HEX (computer CI-V address, usually E0h)

// overwritten by argv[1], and malloc'ed() [and free'ed] in main()
char * serialport = "/dev/ttyUSB1";

#include <stdio.h>    // standard IO
#include <string.h>   // string tools
#include <stdlib.h>   // malloc & free
#include <unistd.h>   // usleep & write
#include <time.h>     // localtime, strftime
#include <sys/time.h> // gettimeofday
#include <fcntl.h>    // file control - used for serial port setup
#include <termios.h>  // terminal control - used for serial port control

// defines and typedefs
typedef unsigned long int  u4;
typedef struct ranctx { u4 a; u4 b; u4 c; u4 d; } ranctx;
#define rot(x,k) (((x)<<(k))|((x)>>(32-(k))))

// some declares
int open_port(void);
void sendtorig(long unsigned int);
unsigned int str2hex(const char * s);
u4 ranval( ranctx *x );
void raninit( ranctx *x, u4 seed );

// global variables
int port = 0;
ranctx PRNG;
unsigned int tCal;

int main(int argc, char **argv)
{
	//unsigned int n_hop = sizeof(hopping_frequencies)/sizeof(hopping_frequencies[0]);
	//int i = 0;
	time_t curtime;
	struct timeval tv;
	char buffer[30];
	unsigned int R, F, T;
	
	printf("\033[2J");
	printf("M1GEO - RigHop - Jumps Radio TRX Frequency in time.\nCurrent Timestamp:  ");
	
	gettimeofday(&tv, NULL);
	curtime=tv.tv_sec;
	strftime(buffer, 30 ,"%d/%m/%Y %T.", localtime(&curtime));
	printf("%s%06ld - Must be NTP Synced.\n", buffer, tv.tv_usec);
	
	if (argc != 4) {
		printf("\n\tusage:\t\t%s serial_port radio_civ seed\n", argv[0]);
		printf("\texample:\t%s /dev/ttyUSB0 0x88 1234\n", argv[0]);
		return -1;
	}
	
	serialport = (char *) malloc(strlen(argv[1])+1);
	strcpy(serialport, argv[1]);
	
	rigaddress = str2hex(argv[2]);
	
	// seed PRNG
	raninit( &PRNG, atoi(argv[3]) );
	
	//// TODO - DOES NOT WORK! NOT UINQUE ACROSS COMPUTERS!
	//printf("Generataing Hopping Patterns from seed '%d': ", atoi(argv[3]));
	//for (i=0; i<60; i++) {
		//hopping_pattern[i] = ranval(&PRNG) % n_hop; // get PRNG value
	//}
	//printf("OK\n");
	
	//printf("Selected Hopping Frequencies: ");
	//for (i=0; i<60; i++) {
	//	printf("   %u:\t%.4f MHz\n", i, (double)((double)hopping_frequencies[hopping_pattern[i]]/(unsigned int)1e6));	
	//}
	//printf("\n");
	
	
	//termios - structure contains options for port manipulation
	struct termios specs; // for setting baud rate 

	//setup part
	printf("Opening serial port '%s' at 19200 for CI-V Address 0x%X.\n\n\n\n\n", serialport, rigaddress);
	port = open_port();
	if (port < 0) {
		return -1;
	}
	tcgetattr(port, &specs); 

	//now the specs points to the opened port's specifications
	specs.c_cflag &= ~PARENB;
	specs.c_cflag &= ~CSIZE;
	specs.c_cflag |= CS8;

	//output flags
	//CR3 - delay of 150ms after transmitting every line
	specs.c_oflag = (OPOST | CR3);

	//set Baud Rate to 19200bps
	cfsetospeed(&specs, B19200);
	
	//our custom specifications set to the port
	//TCSANOW - constant that prompts the system to set
	//specifications immediately.
	tcsetattr(port, TCSANOW, &specs);
	
	// main loop
	while (1)
	{
		// get the current system clock
		gettimeofday(&tv, NULL);
		
		// work out time to next interval, and then set timer
		
		T = (1E6 - tv.tv_usec - tCal);
		usleep(T);
		
		//update for actual running time
		gettimeofday(&tv, NULL);
		curtime=tv.tv_sec;
		
		// shuffle average along 1
		if (tv.tv_usec < 5E5) {
			tCal += (tv.tv_usec / 2);
		} else {
			tCal -= ((1E6-tv.tv_usec) / 2);
		}
		
		if (tCal > 1E3) {
			tCal = 0;
		}
		
		if (tv.tv_usec >= 5E5) {
			R = hopping_pattern[((tv.tv_sec+1)%60)];
		} else {
			R = hopping_pattern[tv.tv_sec%60];
		}
		F = hopping_frequencies[R];
		
		// push frequency to radio
		sendtorig(F);
		
		// print wakeup time
		printf("\033[3A\r"); // jump up 2 lines
		strftime(buffer, 30 ,"%d/%m/%Y, %T.", localtime(&curtime)); printf("\tTimestamp:\t%s%06ld\n", buffer, tv.tv_usec);
		printf("\tFrequency:\t%.4f MHz\n", ((double)F/(double)1E6));
		printf("\tTime Cal:\t%u us (T=%u us)\n", tCal, T);
		fflush(stdout);
		
	}
	free (serialport);
	return 0;
}

// function to open the port
int open_port(void)
{
	int port;
	//open the port and store the file descriptor in 'port'
	port = open(serialport, O_RDWR | O_NOCTTY | O_NDELAY);
	if (port == -1){
		// Could not open the port
		printf("open_port: Unable to open '%s'\n", serialport);
		return -1; // failed
	} else {
		fcntl(port, F_SETFL, 0); //leave this
	}
	return (port);
}

unsigned int str2hex(const char * s) {
	unsigned int result = 0;
	int c ;
	if ('0' == *s && 'x' == *(s+1)) { s+=2;
		while (*s) {
			result = result << 4;
			if (c=(*s-'0'),(c>=0 && c <=9)) result|=c;
			else if (c=(*s-'A'),(c>=0 && c <=5)) result|=(c+10);
			else if (c=(*s-'a'),(c>=0 && c <=5)) result|=(c+10);
			else break;
			++s;
		}
	}
	return result;
}

// This function impliments the very basic command to set radio frequency
// It apparently works with ANY Icom radio supporting CI-V.
// CI-V Addresses set globally
//
void sendtorig(long unsigned int f) {
	// ropey code that converts integer to BCD - it was late!
	char fE = (((f/10)%10)<<4) + ((f/1)%10);
	char fD = (((f/1000)%10)<<4) + ((f/100)%10);
	char fC = (((f/100000)%10)<<4) + ((f/10000)%10);
	char fB = (((f/10000000)%10)<<4) + ((f/1000000)%10);
	char fA = (((f/1000000000)%10)<<4) + ((f/100000000)%10);;
	char tosend[] = {0xFE, 0xFE, rigaddress, computerad, 0x05, fE, fD, fC, fB, fA, 0xFD};
	int n = write(port, tosend, sizeof(tosend)/sizeof(tosend[0])); // i = no of bytes written
	if (n<0) {
		printf("Comms failed: %s (%d bytes)\n", serialport, n);
	}
}

u4 ranval( ranctx *x ) {
    u4 e = x->a - rot(x->b, 27);
    x->a = x->b ^ rot(x->c, 17);
    x->b = x->c + x->d;
    x->c = x->d + e;
    x->d = e + x->a;
    return x->d;
}

void raninit( ranctx *x, u4 seed ) {
    u4 i;
    x->a = 0xf1ea5eed, x->b = x->c = x->d = seed;
    for (i=0; i<20; ++i) {
        (void)ranval(x);
    }
}
