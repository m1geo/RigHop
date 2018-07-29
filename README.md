# RigHop
Program to sync frequency hopping of an Icom amateur radio transceiver using an NTP synced PC clock and CI-V.

Program compiles with simple make file:  "make"

User can specify hopping frequencies, starting seed, and easily tweak any functionality required.

To run the program, use:  "righop port portspeed CIV seed"

 - port is the Unix port, for example /dev/ttyUSB0
 - portspeed speed (usually 19200 for older radios, 115200 for newer)
 - CIV is the CI-V address of the radio, for example 0x88 for IC7100, 0x98 on IC7610
 - seed is the starting seed for the frequency hop generation. All stations must use the same seed.

George
M1GEO
