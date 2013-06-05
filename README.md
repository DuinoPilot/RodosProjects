Collected works of my RODOS projects
======================================

Task 1
=======
1 Write a thread-class that outputs "Hello World" and the threadname once.

-> threadname should be given to constructor
-> create 3 or more threads (objects) to test the behavior

2 same as Linux exercise "static scheduling"

a) output the time and the threadname every 1, 2, 5 and 11 seconds by different 
threads
-> threadname and periode should be given to constructor

b) output the time and the threadname once at 30 seconds by a fifth thread
-> threadname and time should be given to constructor

3 Write a thread-class where the objects resume each other as shown in the picture.
-> insert a small break before or after every output
class RingElement : public Thread {...};
RingElement a("A"), b("B"), c("C"), ...;
Output: A B C D E F G H A B C D E F G H ... (or vice versa)