# Studio 20
1. We need to make sure we delete the pointer in our password proxy class so that we do not run into any memory leaks. 
We are allocating a new pointer to the same object, and that object might eventually get deleted. When this happens, we 
need to make sure the pointer we created in the password proxy class doesn't end up as a dangling pointer. We do this 
by making sure we delete it.
2. I ran tests to make sure the password proxy class worked. I created a file object, added it to the password proxy class, 
and then made a visitor object so that I could call accept on the file. I ran all the member functions of the file such as 
read, write, and accept but through the password proxy so that it required a password input. I observed that everything worked 
as intended and I was being prompted for a password. When I input the wrong password it wouldn't let me run the functions, so 
that meant everything was working properly. I tested for incorrect passwords and tested to make sure the functions of the file 
still worked correctly, printing out correct images and making sure that the read function would override the current file contents 
with the new vector.
3. I did not run into any errors when running the test suite.