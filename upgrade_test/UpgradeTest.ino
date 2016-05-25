// optiboot-service upgrade test
#include "optiboot-service.h"
#include "Arduino.h"
#include "avr/pgmspace.h"


//const uint16_t	MS=16384;

const uint16_t	MS=((FLASHEND+1)-512)>>1;
void setup() {
	Serial.begin(115200);
	Serial.print(F(__FILE__));
	// initialize digital pin 13 as an output.
	pinMode(13, OUTPUT);
	char	s[SPM_PAGESIZE];
	uint16_t i;
	uint16_t L=20;
	uint16_t	k=0;
	Serial.print(MS);
	uint16_t	end=MS+MS;
	for(i=MS;i<end;i+=SPM_PAGESIZE){
//	i=MS;
		{
			int ii;
			for (ii = 0; ii < SPM_PAGESIZE; ii++) {
				if (ii & 1) {
					s[ii] = 'A' + (k & 15);
				} else {
					s[ii] = 'a' + ((k >> 4) & 15);
				}
			}
		}
		Serial.println(i);
		Serial.println(end);
		optiboot_service('F',s,i,SPM_PAGESIZE);
		Serial.println(i);
		k++;
	}

	optiboot_service('X',s,MS,SPM_PAGESIZE);
	// bye-bye sasha!

}

void loop() {
	int i
	;
	int L=20;
	for(i=0;i<SPM_PAGESIZE;i++){
		Serial.print(pgm_read_byte(MS+i));
		Serial.print('.');
	}
	Serial.print('\r');
	Serial.print('\n');
	Serial.print(MS);

	Serial.print('\r');
	Serial.print('\n');
	digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(100);              // wait for a second
	digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
	delay(500);              // wait for a second
}


