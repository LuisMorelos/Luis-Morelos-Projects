# Studio 21
1. When a destructor is called on the base class, we also need to call it on the correct derived class to avoid 
lifetime memory issues such as memory leaks. By making the base class destructor virtual, we ensure that the derived 
class destructor is also called.
2. Since the command prompt does not know about the other objects, it doesn't need to conern itself with how they work. 
We could very easily replace the file factory with a new one or the file system with a new one and the command prompt would 
not care. We have detatched it from the other classes and therefore made our code easier to modify, fix, and expand. This 
makes it very flexible and reusable since it is essentially a shell that we fill with the other class objects we create.
3. I created a file system, touch command, and file factory object that I used to configure the command prompt object. I then 
called run and tested all possible command line arguments such as help, quit, help followed by a command, etc. I also tried 
invalid inputs to make sure my code would work properly when used incorrectly. I then quit and opened a file using the touch 
command to make sure that that worked. All the tests performed exactly as expected and I was able to move on to the test 
suite.