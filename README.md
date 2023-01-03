MusicTool is a simple interpreter in C I'm doing on my spare time to get better at the language.

I am doing it from scratch n with 0 previous knowledges of how interpreters are normally built which means that a lot of things are a bit janky.  
However I find it cool to try n figure out how to make an interpreter before learning the theory on how to do it. (Which I'll do for my next interpreter project bc it will be more ambitious)

MusicTool should work on Linux,  Windows and MacOS however I never tested it on a Windows or Mac so I'm not sure.

This version of MusicTool is currently not finished.
However it has most of the features I was planning on having at first which include: 
-a scale/modes/chprog generation system 
-a command line interpreter 
-a way to interpret commands from a file 
-a way to load/write an environment from/to a file
-a basic save system

Some key features I'd like to add before releasing the 1.0 version are: 
-a proper syntax checker 
-a way to check if a scale/harmo/chprog already exists in an environment n if so not save/write it again.


Due to the lack of an actual syntax checker the parsing from command line is a bit buggy. Everything that "should be" correct is 
but some commands that "should be" incorrect sometimes aren't.
