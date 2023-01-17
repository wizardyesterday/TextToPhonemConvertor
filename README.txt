Years ago, there was an article in the Circuit Cellar column of Byte
Magazine that discussed converting text to speech using sound rules.  This
may have been back in 1984. I had decided to build a synthesizer ('ll scan
the schematic and upload it when I find it) and write software in
Pascal/MT+ on a CP/M machine.

There is some Z80 assembly language code that I wrote so that I could output
data to/input data from the required I/O ports (the parallel port) to drive
the synthesizer with a byte stream of encoded phonem values to make it talk.

I've uploaded this application for historical reasons, and I'd like to share
this work with the public.  It's not the best parser around (it may be the
*worst* parser), but this app did the job for me.

I've noticed that the Festival application that I've played with on my
Linux system produces similar sound quality (maybe better), so this code
provides no additional information other than to portray *another* way to
do things.

If anything, people may chuckle with respect to my coding style back in
1984.

Chris G. 10/31/2020

-------------------------------------------------
01/05/2023
-------------------------------------------------
I have added the original NRL paper for which this work ws derived.  It
resides in the Papers directory.


-------------------------------------------------
01/07/2023
-------------------------------------------------
I have created a Votrax directory that containes the above mentioned
paper, the Votrax SC-01 datasheet, and photos of my home-built speech box.
I have to figure out where I put the design notes (schematic and stuff).
It's somewhere in my lab, I hope. Once I find the design notes, I'll scan
them and post them in a Design directory.

I think I want to port this Pascal/MT+ code into C or C++ code. I'll have
to create a Votrax SC-01 software subsystem that accepts a phonem and outputs
a PCM sample stream representation of the phone to stdout. I can then pipe
the output to aplay so that I can hear the synthesizer output.

-------------------------------------------------
01/11/2023
-------------------------------------------------
I found the Byte Magazine articles!  The system is called the Microvox Text
to Speech Synthesizer.  It has a 6502 processor for which its software
drove the SC-01 chip.  The Byte issues are September 1982 (hardware) and
October 1982 (software).  My system did not have a processor in it.  It was
a peripheral box for which the host computer sent information to the system
via a parallel port interface.  The peripheral board in my computer was a
3P+S board.

-------------------------------------------------
01/12/2023
-------------------------------------------------
The design is now captured.  The pdf file looks sucky, but the jpegs are not
too bad. I especially wanted to capture the signal definitions on the DB-2b
connector.  After perusing the schematic, it is clear that 10 bits of I/O
are needed: 6 bits for the phonem code, 2 bits for the inflection code,
1 bit for the strobe, and 1 bit for reading the status of the SC-01 chip.

-------------------------------------------------
01/16/2023
-------------------------------------------------
I have created a CplusPlusPort directory that contains my work related to
porting the Pascal/MT+ code to C++.  Many of the Pascal functions and
procedures use the 'var' keyword before some of the parameters.  As as
known this implies that the address of the parameter is passed to the
procedure/function.  Originally, I decided to replace the 'var' parameters
with pointers to the arguments.  The changes to the source code became far
too cumbersome, so I decided to use reference parameters instead.  This way,
the only thing I have to change is the signature of each function.  That is,
instead of using (int *myvalue), I use (int& myvalue).

I wrote rapid prototype code in C++ to make sure that things worked as I
expected, and I see that this should work fairly well.

