# Studio 18
1. We would have to modify the create file method to be able to recognize different types of files and this would probably 
take a lot of work. It makes it so that adding a new file type is tedious and takes a lot of tweeks in multiple places in the 
code. Separating the file system from the files sounds like a great way to make this whole process more efficient and easier 
to manage as a programmer.
2. We would need to create a new concrete file factory class if there were a new file that takes COMPLETELY different steps to 
create. A file that is so vastly different to create that it can't share a file factory class with any of our previous file types. 
You would only need to modify the file factory class to recognize and be able to create a new type of file. You really only need to 
change the code in this one place. If you have two implementations that use the same files then you can definitely use the same 
file factory since you are dealing with identical files and therefore identical file creation. If your implementations use different 
files you could modify your file factory to create files for both implementations and use the same file factory, but it would probably 
be better practice to create two different file factories.
3. I created the two pointers and tested the creation of new files with the simple file factory instead of the simple file system. I made 
sure to try and open, write, read, and close the files but this is mostly implementation from the file system which I already extensively 
tested in studio 17 so I wasn't too worried. I mostly wanted to make sure that the file factory could properly create files and it was 
able to do so successfully. I wrote random messages such as "hello world" into the newly created files and input random images made up of 
different configurations of X's as well. It was able to detect incorrectly shaped image vectors and was able to correct the correct type of 
file I wanted based off of the ending part of the file's name (.txt or .img).
4. At this point the simple file system only relies on the abstract file interface since it is not worried about distinguishing different 
types of concrete file types.