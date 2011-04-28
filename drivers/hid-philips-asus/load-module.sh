#!/bin/sh
# This script forces loading hid-philips-asus module before usbhid

MODINFO=`modinfo hid-philips-asus 2>/dev/null`
if [ -z "$MODINFO" ]; then
	echo "Module 'hid-philips-asus' is not installed."
	exit
fi

# get list of existing hid modules
MODULES=`lsmod|grep hid| cut -d " " -f 1 | grep hid`

# unload them
echo "Unloading existing hid modules."
for module in $MODULES; do
	modprobe -vr $module
done

echo "Loading hid_philips_asus module."
# load hid_philips_asus first
modprobe -v hid_philips_asus

echo "Reloading other hid modules."
# load the rest modules
for module in $MODULES; do
	modprobe -v $module
done
