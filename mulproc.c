/*
 This program will fork two child processes running the two programs generated in programming zero in parallel.
 Hint: You mant need to use fork(), exec() family, wait(), exit(), getpid() and etc ...

 Requirements:

 1) Exactly two child processes are created, one to run testspecial program and the other is to run testalphabet program;
 2) When a program starts to run, print a message to the output screen showing which process (with PID) is running which program, for example:
    "CHILD <16741> process is executing testalphabet program!"

 3) When a program is done, the process exits and at the same time, a message should be print to the output screen showing which  process (with PID) is done with the program, for example:
    "CHILD <16741> process has done with testalphabet program !"

 4) The messages should match the real execution orders, i.e. when the testspecial program starts/ends, the right message should be print out. So you need to figure out how to get the starting/ending time of each
 process.


 The expected screen print out should be similar as follows:

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
 */
/*
 * Info:
 * Alan Ta
 * 819357091
 * cssc2363
 * CS570 Summer
 * Program 1: Letter and character frequency counter with multiprocessing
 * Due: 07/19/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
int main(void) {
    // Creates process IDs for the letter and special character child
    pid_t letterChild, charChild;
    letterChild = fork(); // Creates new process with letterchild's ID
    if(charChild < 0 || letterChild < 0){
        fprintf(stderr, "Fork has failed \n");
    } // if "this" process is letterchild, get the process idea
    if(letterChild == 0){
        letterChild = getpid();
        fprintf(stdout, "CHILD <%d> process is executing testalphabet program !\n", letterChild);
        // Print the statement regarding the process and execute the executable with execvp
        execvp("testalphabet",NULL);

    } // If the first if statement is passed, then create the second process for special characters
    else {
        charChild = fork();
        if(charChild == 0){
            charChild = getpid();
            fprintf(stdout, "CHILD <%d> process is executing testspecial program !\n", charChild);
            execvp("testspecial", NULL);
            // Performs the same as letter child, but executes the special character executable
        }
    }
    // A catch all scenario, whether alphabet or special character finishes
    // Waits for either the letterChild or charChild to finish
    // If one finishes first, then wait for the other to finish
    pid_t whichChild = wait(NULL);
    if(whichChild == letterChild){
        fprintf(stdout, "CHILD <%d> process has done with testalphabet program !\n", letterChild);
        pid_t otherChild = wait(NULL);
        if(otherChild == charChild)
            fprintf(stdout, "CHILD <%d> process has done with testspecial program !\n", charChild);
    }
    // If the special character process finishes first
    if(whichChild == charChild){
        fprintf(stdout, "CHILD <%d> process has done with testspecial program !\n", charChild);
        pid_t otherChild = wait(NULL);
        if(otherChild == letterChild)
            fprintf(stdout, "CHILD <%d> process has done with testalphabet program !\n", letterChild);
    }
    // Will wait till all child processes finish
    //wait(NULL);
    return 0;

}