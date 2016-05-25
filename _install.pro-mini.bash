D=./optiboot/bootloaders/optiboot/
make -C $D ISPTOOL=avrisp ISPPORT=/dev/ftdi ISPSPEED=-b19200  BAUD_RATE=57600 atmega328_isp LED_START_FLASHES=0
