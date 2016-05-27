avrdude  -c arduino -p atmega328p -P /dev/ftdi_A501JSC6 -b 57600 -U flash:r:tmp.flash.raw:r

md5_c="`head -c $[ 32768 - 512 ] tmp.flash.raw|md5sum|awk '{print $1}'`"
md5_e="ebccc9486ab83cf4b3f3b38ae0b9d584"

if [ "$md5_c" == "$md5_e" ];then
	banner ok
else
	banner ">error<"
fi

