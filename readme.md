Info:
Alan Ta
819357091
cssc2363
CS570 Summer
Program 1: Letter and character frequency counter with multiprocessing
Due: 07/19/2020
Program Description: 

Files included:
mulproc.c
makefile
testspecial
testalphabet
readme.md

Libraries:
#include <stdio.h> - fprint
#include <stdlib.h>
#include <sys/wait.h> - wait(NULL)
#include <unistd.h> - fork(), execvp()


How to run:
Warning: This program 1 is fundamentally the same as program 0 such that it requires a data and result directory in order to function. 

:make // To compile the program

:./mulproc // To run the executable 

The result should print on screen:
**************************************************************
 CHILD <16741> process is executing testalphabet program!
 CHILD <16742> process is executing testspecial program!
, -> 745668
. -> 798072
... ...

CHILD <16742> process has done with testspecial program !
a -> 2861232
b -> 494472
... ...

CHILD <16741> process has done with testalphabet program !
***************************************************************

Design & Code explaination:
First I created a process id for the letterChild and charChild (Special Character). I then have the parent fork the letterChild and have it execvp the letter executable (testalphabet). Execvp allows the child process the execute an executable while the parent is still running its own jobs. As the parent continues it will then fork the second child (special character) and execvp the specialtest executable. I set up the both children with an if else statement for the parent process. if ( equals the letterChild) execvp, else fork charChild (second child). From the parents point of view, the first if statement is only for the first child process. If its not the first child, then its the parent still thus fork the second child and IF that process is the second, (charChild == 0), then now its the second child and execvp etc...
This processes will run until finish. I used execvp because I've used it before. 

execvp("testalphabet",NULL);
// The first argument is the filename, which is the executable in the directory, and the second is the argv, but because it was set to void, I set it to NULL 
 
In order to get the processes to finish before the parent can end its process, I created another pid_t (process id) and set that to wait for a process to finish. This is where it gets interesting. Typically the special character process finishes first because it uses the fewest comparison and is also less of those characters. But this case is only true for the given data set. There could be a data set where there are more special characters SO
I created a catch all set of if statements. The first if statement checks if the first process to finish is the letterChild. If it is, print that that process has finished and then create another pid_t = wait(NULL) and have an if statement to catch the other child.

if(whichChild == letterChild){
        fprintf(stdout, "CHILD <%d> process has done with testalphabet program !\n", letterChild);
        pid_t otherChild = wait(NULL);
        if(otherChild == charChild)
            fprintf(stdout, "CHILD <%d> process has done with testspecial program !\n", charChild);
    }
Here is the code to help get a better understanding. I initially thought that if I just had two wait(NULL) then it should work, but when I tested it out, the process will just end regardless without the fprint() OR the parent process would finish and leave the child process as a zombie. There is another set of code with the inverse (charChild and letterChild respectively) IF the charChild somehow finishes first. 
Then I set a final wait(NULL) just in case. This will wait for any left over processes. But in my testing I notice that my IF statements work and there seems to be no real point of having it. 

Possible Improvements/Alternate Designs:
I know in the professor's weekly reading/lectures, the fork video provides an example on having multiple forks using a FOR loop. I thought this was interesting, but I had already came up with my design using the IF ELSE statement before watching the video.