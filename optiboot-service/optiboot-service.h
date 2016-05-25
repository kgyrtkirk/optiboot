/*
 * optiboot-service.h
 *
 *  Created on: May 25, 2016
 *      Author: Zoltan Haindrich (kirk)
 *
 * Special thanks to majekw for the "spm" feature.
 * I've borrowed a lot of your ideas and even some api docs!
 * https://github.com/majekw/optiboot/tree/spm
 */

#pragma once
#include <avr/boot.h>

typedef void (*optiboot_service_t)(uint16_t address, uint8_t command, uint16_t data);

/*
 * Devices with more than 64KB of flash:
 * - have larger bootloader area (1KB) (they are BIGBOOT targets)
 * - have RAMPZ register :-)
 * - need larger variable to hold address (pgmspace.h uses uint32_t)
 *
 * To not do many ifdefs and don't confuse users I declared new 'always valid'
 * type to declare address: optiboot_addr_t.
 */
#ifdef RAMPZ
typedef uint32_t optiboot_addr_t;
const optiboot_service_t do_spm = (optiboot_service_t)((FLASHEND-1023+2)>>1);
#else
typedef uint16_t optiboot_addr_t;
const optiboot_service_t do_spm = (optiboot_service_t) ((FLASHEND - 511 + 2) >> 1);
#endif

/*
 * The same as do_spm but with disable/restore interrupts state
 * required to succesfull SPM execution
 *
 * On devices with more than 64kB flash, 16 bit address is not enough,
 * so there is also RAMPZ used in that case.
 */

void do_spm_cli(optiboot_addr_t address, uint8_t command, uint16_t data) {
	uint8_t sreg_save;

	sreg_save = SREG;  // save old SREG value
	asm volatile("cli");
	// disable interrupts
#ifdef RAMPZ
	RAMPZ=(address>>16) & 0xff;  // address bits 23-16 goes to RAMPZ
	do_spm((address & 0xffff),command,data);// do_spm accepts only lower 16 bits of address
#else
	do_spm(address, command, data); // 16 bit address - no problems to pass directly
#endif
	SREG = sreg_save; // restore last interrupts state
}
