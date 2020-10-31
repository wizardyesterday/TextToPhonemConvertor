Years ago, there was an article in the Circuit Cellar column of Byte
Magazine that discussed converting text to speech using sound rules.  This
may have been back in 1984. I had decided to build a synthesizer ('ll scan
the schematic and upload it when I find it) and write software in
Pascal/MT+ on a CP/M machine.

There is some 8080 assembly language code that I wrote so that I could output
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

Chris G. 11/01/2020

