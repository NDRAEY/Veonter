#!/bin/sh
set -e

. ./iso.sh
qemu-system-i386 -m 64M -hda disk.img -audiodev pa,id=audio0 -M pcspk-audiodev=audio0 -cdrom Veonter.iso -serial mon:stdio -boot d -s -S
#. ./clean.sh

