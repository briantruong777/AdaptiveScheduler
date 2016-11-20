#!/bin/bash
set -e

# Note that this probably only works on Linux kernel 4.4.0-45 for Ubuntu. You
# may need to run `sudo apt-get build-dep linux-image-$(uname -r)` for any
# missing dependencies.

LINUX_DIR=linux-4.4.0

if [[ ! -e "$LINUX_DIR/debian/rules" ]]; then
    echo "Couldn't find debian/rules so extracting now..."
    if [[ ! -e "*.dsc" ]]; then
        echo "Couldn't find *.dsc file, downloading now..."
        apt-get source linux-image-4.4.0-45-generic --download-only
    fi
    dpkg-source -x *.dsc
fi

# Enable ccache if is installed and not yet enabled
if hash ccache; then
    echo $PATH | grep -q ccache || export PATH="/usr/lib/ccache:$PATH"
else
    echo "No ccache found, please consider installing ccache to speed things up"
fi

# Build and install Linux kernel for Ubuntu
cd $LINUX_DIR
fakeroot debian/rules clean
fakeroot debian/rules binary-headers binary-generic
cd ..
sudo dpkg -i linux-headers-* linux-image-*

#read -p "Reboot machine (y/n)? " input
#case $input in
#    [Yy]* ) reboot;;
#    * ) ;;
#esac
