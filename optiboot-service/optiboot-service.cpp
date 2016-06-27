#include "Arduino.h"
#include "optiboot-service.h"

void optiboot_service(int8_t memtype, void *mybuff,uint16_t address, pagelen_t len) {
	uint8_t sreg_save;

	sreg_save = SREG;  // save old SREG value
	asm volatile("cli");
	// disable interrupts
#ifdef RAMPZ
	// FIXME: this RAMPZ is messy...and it handled badly inside the bootloader too...i go forward for my pro minis ;)
	Serial.println("not supported at: ");
			Serial.println(__FILE__);
//	RAMPZ=(address>>16) & 0xff;  // address bits 23-16 goes to RAMPZ
//	do_spm((address & 0xffff),command,data);// do_spm accepts only lower 16 bits of address
#else
	do_spm(memtype, (uint8_t*)mybuff, address,len); // 16 bit address - no problems to pass directly
#endif

	SREG = sreg_save; // restore last interrupts state
}
