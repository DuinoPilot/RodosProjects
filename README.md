Collected works of my RODOS projects
======================================

[DLR - RODOS](http://software.dlr.de/p/rodos/home/ "DLR")

[WIKI - RODOS](http://en.wikipedia.org/wiki/Rodos_\(operating_system\) "WIKI")


[Task 1](/tree/master/Task1)
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

[Task 2](/tree/master/Task2)
========
1) Working with global variables

a) Write a small programm that shows the increment-errors when two or more threads access the same global variable.

-> define the global variable volatile !!!

b) protect the global variable with a semaphore

2)
In the picture below you can see a terminal window with the lettre "R" in the left top corner. 
This is your robot you shall move to the target "#". You can set speed and direction of the robot by publishing the appropriate middleware topic. There are 5 other topics to get the status of the robot and the position of the traget. The middleware topics are defined in "robot_topics.h".

![Alt text](/console.png)
a) use one (or more) simple subscriber (and a thread) 

b) use one (or more) fifo as subscriber (and a thread)
