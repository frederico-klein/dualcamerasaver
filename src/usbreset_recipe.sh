#!/usr/bin/env bash
###note: when the cameras really crash, this didn't really work...

cc usbreset.c -o usbreset
chmod +x usbreset

lsusb  | grep 8086 ### this is the realsense vendor number(?)

# Bus 003 Device 023: ID 8086:0ad3 Intel Corp.
# Bus 003 Device 024: ID 8086:0ad3 Intel Corp.

sudo ./usbreset /dev/bus/usb/003/023
sudo ./usbreset /dev/bus/usb/003/024
