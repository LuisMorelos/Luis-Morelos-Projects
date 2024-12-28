# Studio 16
1. Team Members: Luis Morelos
2. To declare an interface in c++ you can create an abstract class. This is a class that has pure virtual methods. These functions 
then define the interface methods that derived classes must override.
3. This is an example of interface inheritance since AbstractFile is an abstract class and doesn't have any implementations of its 
own. TextFile will have to provide its own implementations of virtual methods.
4. We probably want our member variables to be private. Making them public should generally be avoided for safe coding practices 
and making them protected would only matter if we want to make other derived classes of our current class. In this case, our class 
is already a derived class, so private makes the most sense.
5. I ran all the functions to make sure they worked. The write function was able to insert characters onto the vector, the read 
function was able to print the contents of the file, the write function was able to delete what was there before and replace it 
with new chars, the append function was able to add chars without replacing old ones, and finally the getters were able to retrieve 
the correct information about my file. I ran tests by printing out what was returned from the getters and it printed out what was 
expected.
6. I made a reference of type AbstractFile that equals the text file object. I then called all of the functions I already called 
but on the reference of type AbstractFile instead of the text file object.