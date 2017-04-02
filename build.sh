#!/bin/bash

while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -o)
    O=y
    shift
    ;;
    -a)
    A=y
    shift
    ;;
    -h)
    ADDR="$2"
    shift 2 # past argument
    ;;
    *)
        shift    # unknown option
    ;;
    esac
done

echo "Building"
mkdir -p bin
if [ "$O" = y ]
    then make > bin/buildmsg.txt
    else make &> bin/buildmsg.txt
fi
echo "Converting to hex."
avr-objcopy -j .text -j .data -O ihex bin/out.o bin/out.hex
if [ -z "$ADDR" ]
    then
        exit
fi
echo "Uploading to pi."
scp bin/out.hex pi@$ADDR:~/bin/out.hex
echo "Kill node"
ssh pi@$ADDR 'killall node'
echo "Uploading to avr"
ssh pi@$ADDR 'sudo avrdude -p atmega328 -C ~/avrdude_gpio.conf -c pi_1 -v -U flash:w:bin/out.hex' &>bin/avrdude.txt
echo "Done."