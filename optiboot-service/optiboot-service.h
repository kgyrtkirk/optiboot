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

/*
 * We can never load flash with more than 1 page at a time, so we can save
 * some code space on parts with smaller pagesize by using a smaller int.
 */
#if SPM_PAGESIZE > 255
typedef uint16_t pagelen_t ;
#else
typedef uint8_t pagelen_t;
#endif

typedef void (*optiboot_service_t)(int8_t memtype, uint8_t *mybuff,uint16_t address, pagelen_t len);
//typedef void (*optiboot_service_t)(uint16_t address, uint8_t command, uint16_t data);

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
 * currently: E: eeprom
 * 				X: exchange
 * 				others: flash
 */

void optiboot_service(int8_t memtype, void *mybuff,uint16_t address, pagelen_t len);
