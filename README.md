AdaptiveScheduler
=================
UIUC CS 523 Semester Project

This repo contains a fork of the Linux kernel as well as various benchmarking
scripts. All modifications to the Linux kernel were designed and tested for
Ubuntu Server 16.04.1 LTS.

## Building the kernel
The `./build_kernel.sh` script will run the standard Ubuntu build process which
will create an Ubuntu package that installs the custom kernel. It will also
automatically install the package as well which will require root access (it
will prompt for sudo). This takes approximately 40 minutes to a couple hours
depending on CPU/disk perfomance, ccache, etc.
