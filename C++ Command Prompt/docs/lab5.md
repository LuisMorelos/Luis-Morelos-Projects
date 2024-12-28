# Lab 5
Group Members: Luis Morelos 518478
Work distribution: I did all of it

Testing:
I was able to successfully run the entire test suite without errors after some debugging, but I found that, even if all the parts worked 
individually, they might not look good together. For this reason, I ran through some command prompt actions in main. I made sure that I 
could input incorrect commands or gibberish and the command prompt would still continue. I also made sure I could always quit and could 
always ask for help. I tested out individual commands' display info functions, and then tried running actual commands. To do this, I had 
to create a pointer to an abstract command object that would be the command. I would fit this command with the file system I had set up 
and I would then use the command prompt's add command function to make sure it was in there. Once this was done, I would run through an 
example of the command by running the command prompt. I created files using touch, created password protected files as well, wrote to them 
using cat, read them using display, copied them using copy, displayed all files using ls, and finally removed them using remove. I then 
created a macro command object that I fitted with the rename parsing strategy, copy command, and remove command. This would serve as the 
rename command. I also created a macro command fitted with a new parsing strategy I made for step 9 called the write to new parsing strategy.
This strategy takes the command name "touchcat" and creates a file. It then allows you to immediately write to it. I had to check for flags 
such as -p and -a. -p must always come before -a, but it was possible that the user only input -a and not -p. For this reason, I had to 
check the flags and see if there was one or two. I would then check to see if the first one needed to be fed to the touch command or the 
cat command. I tested these by running through them and renaming files, which worked, as well as creating new files and writing to them 
immediately, which also worked. For this reason, my new macro command takes this form: touchcat "filename" [-p] [-a]. I put the -a after 
the -p since touch always runs first.

Errors:
I ran into quite a few errors while running the test suite as well as main. In main, the only problem I had was that the command prompt 
class was not feeding arguments correctly to commands. This was causing the commands to not run, and so I had to fix this with some simple 
logic fixes to the parsing strategy of my command prompt. In the test suite though, there were more things I had to fix. In the copy command 
class, I was accidentally deleting the original file from the file system, so I stopped deleting it and only closed the file. In the ls 
command class I was not correctly spacing out the file names when displayed, so I made sure the spaces were added correctly. In the cat 
command class I was adding too many end of line characters (\n), so I had to fix how many of those I was outputting. In the password proxy 
class I was accidentally deleting the password proxy object right after it was created, which was giving me errors when that file was accessed 
since it was no longer memory saved for the program but rather memory of my actual computer. I had to remove that line of code. I also had to 
make sure that the cat command could not append to image files. Finally, there were some minor tweaks in certain classes in terms of 
formatting and general look, so I fixed those and was finally able to run all 71 tests correctly.