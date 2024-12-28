# Studio 17
1. I ran multiple tests on each function. I created file objects, gave them image vectors of X's and spaces, changed the image vectors, 
and printed them out. This was so that I could see if the functions worked or not. The image function was able to print out the image 
vector I had input through the write function and was able to detect when I was giving it an incorrectly sized image based on the size 
character I added to the end of the image vector. I made sure it was printing out a unique non-zero vector as well. Thankfully they 
worked and I was able to move on.
2. Creating a concrete class is easy at first, but makes it so that when you move on to have multiple classes you have to see specifically 
which one you need and you have to cater to its needs. This makes it really tedious and difficult to expand your code and add new modules 
that add functionality. An interface makes it much easier to track all the information and different classes. It allows you to add new 
classes without worrying too much about how to specifically interact with said classes.
3. You would need to add code to the create file method so that it can recognize new file types and create files for them appropriately. 
You would also need to add a class of this type obviously. For example, you would need to add a music file class and then check for it in 
the create file method.