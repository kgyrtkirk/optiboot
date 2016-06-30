#!/bin/bash
set -e

DEV=/dev/ftdi

D=./optiboot/bootloaders/optiboot/
make -C $D ISPTOOL=avrisp ISPPORT=$DEV ISPSPEED=-b19200  BAUD_RATE=57600 atmega328_isp LED_START_FLASHES=0
if [ -e preshared.key ] ; then
	sleep 3
	avrdude  -c avrisp -p atmega328p -P $DEV -b 19200 \
		-U eeprom:w:preshared.key:r
else
	banner skipping key
fi
banner ok
