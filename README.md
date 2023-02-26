MusicTool is a simple interpreter in C I'm doing on my spare time to get better at the language.

MusicTool currently is in it's 1.3.2 version. If you want to check out previous versions look at the previous releases. 

In version 1.3.2 MusicTool loads a default environment from the defaultenv.txt file. If you rename/ move / erase it the coherand functions might not work properly. However you can add stuff to it if you want to.

I am doing it from scratch n with 0 previous knowledges of how interpreters are normally built which means that a lot of things are very janky.  
However I find it cool to try n figure out how to make an interpreter before learning the theory on how to do it. (Which I'll do for my next big interpreter project bc it will be more ambitious)

MusicTool should work on Linux,  Windows and MacOS however I haven't tested it on yet so I don't guarantee it.

MusicTool has close to no dependencies. If you have gcc, make and the glibc installed you should be 
able to build MusicTool from source w/o any issues.

The syntax checker might be buggy , if you encounter any problems/weird behavior feel free to contact me.

To build MusicTool from source just type "make MusicTool" from command line (assuming make is installed on your computer).

MusicTool also comes with smtool, it takes a command as argument and executes it (it's kinda close to a shell command but not really bc the options syntax is different). 
simply type make smtool to build it.

NB: depending on your version of gcc , you might have an issue with the "-std=C11" flag in the makefile, if so simply remove it / update your version of gcc / replace it with the latest C standart 
that your version of gcc supports.
