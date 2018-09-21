#!/usr/bin/env bash
###note: when the cameras really crash, this didn't really work...

cc usbreset.c -o usbreset
chmod +x usbreset
echo "Resetting all cameras!"
INTELCAMS=`lsusb  | grep 8086` ### this is the realsense vendor number(?)
IFS=$'\n'
for x in $INTELCAMS ; do
  TMP=`echo $x | sed 's/Bus /\/dev\/bus\/usb\//' | sed 's/ Device /\//' |  cut -f1 -d":"`
  echo $TMP
  (exec ./usbreset $TMP)
done

# Bus 003 Device 023: ID 8086:0ad3 Intel Corp.
# Bus 003 Device 024: ID 8086:0ad3 Intel Corp.

#sudo ./usbreset /dev/bus/usb/003/023
#sudo ./usbreset /dev/bus/usb/003/024
