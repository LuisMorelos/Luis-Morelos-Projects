# Studio 19
1. I ran tests to create and read files of both the text and image type. I stored the contents returned from the 
read functions in character vectors and displayed them using for loops and cout. This way I could check that everything 
was functioning as intended. I then made changes to the files using write and append and printed the file contents again 
to make sure that everything was working correctly after the changes I made.
2. The interaction pattern starts with the objects themselves. They'll call the accept function and allow the visitor to 
visit them and perform its function. This lets us perform certain actions without the objects knowing the specifics of what 
the visitor is actually doing. In our case, the text and image files have no idea what the visitor is doing but we are allowed 
to call it from their classes using the accept method.
3. Delegation is when a task is split up among several parties or in this case classes. The work that is needed to handle a 
file object includes all sorts of tasks such as writing to it and reading from it. We have delegated the reading portion to 
a visitor class that displays the file contents. This makes it so that the original file class doesn't have to worry about this 
specific job and can therefore have a cleaner interface. We are able to add functionality easily by having all display stuff 
centralized in a visitor class but we are also able to keep the original class free from clutter.
4. The visitor pattern does require each file class to have an accept method, and if we delegate too much, say for example making 
another visitor for writing as well, we would end up with a lot of unique visitors that would create clutter and confusion anyway. 
We would be creating a mess anyway and this would defeat the purpose of a visitor. Based on this example, we should avoid 
using the visitor design pattern when working with classes that don't really require delegation and can have their operations 
confined to one class or when working with classes that won't change often and don't really require the use of a visitor since 
the operations are simple enough to do in one place.