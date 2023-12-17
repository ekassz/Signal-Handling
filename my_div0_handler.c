////////////////////////////////////////////////////////////////////////////////
// Main File:        my_c_signal_handler.c
// This File:        my_div0_handler.c
// Other Files:      send_signal.c , my_c_signal_handler.c
// Semester:         CS 354 Lecture 001 Fall 2023
// Grade Group:      gg7  (See canvas.wisc.edu/groups for your gg#)
// Instructor:       deppeler
// 
// Author:           Emili Robles
// Email:            ejrobles@wisc.edu
// CS Login:         emili
//
///////////////////////////  WORK LOG  //////////////////////////////
//  Document your work sessions on your copy http://tiny.cc/work-log
//  Download and submit a pdf of your work log for each project.
/////////////////////////// OTHER SOURCES OF HELP ////////////////////////////// 
// Persons:          n/a
//
// Online sources:   n/a
// 
// AI chats:         save a transcript and submit with project.
//////////////////////////// 80 columns wide ///////////////////////////////////
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>


//this is to keep track of counter for good division problems
    int division_count;


/*
This is if division fails: print a message stating that a divide by 0 operation was 
attempted, print the number of successfully completed division 
operations, and then gracefully exit the program using exit(0) 
instead of crashing.
*/
void handler_SIGFPE(){
    printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed successfully: %i\n", division_count);
    printf("The program will be terminated\n");
    exit(0);
}

/*
Now we do the same thing but for SIGINT, here we print print 
the number of successfully completed division operations, and 
then exit the program using exit(0).
*/
void handler_SIGINT(){
    printf("\nTotal number of operations completed successfully: %i\n", division_count);
    printf("The program will be terminated.\n");
    exit(0);
}

/*
Purpose:
Prompt for and read in one integer value.
Prompt for and read in a second integer value.
Calculate the quotient and remainder of doing the 
integer division operation: int1 / int2
Print the results as shown in the examples that follow.
Keep a total count of how many division operations 
were successfully completed.
*/
int main(int argc, char* argv[]){
    division_count = 0;
    //signal for sigfpe
    struct sigaction sigfpe;
    memset(&sigfpe, 0, sizeof(sigfpe));
    sigfpe.sa_handler = handler_SIGFPE;

    //check fpe handle
    if(sigaction(SIGFPE, &sigfpe, NULL) < 0){
        printf("Error for SIGFPE");
        exit(0);
    }

    //signal sigint
    struct sigaction sigint;
    memset(&sigint, 0, sizeof(sigint));
    sigint.sa_handler = handler_SIGINT;

    //check alarm handle
    if(sigaction(SIGINT, &sigint, NULL) < 0){
        printf("Error for SIGINT");
        exit(0);
    }

    //loop division
    while(1){
        char buffer[100];

        //Print instruction to ther user
        printf("Enter first integer: ");
        fgets(buffer, 100, stdin);
        //get 1st
        int first_num = atoi(buffer);
        printf("Enter second integer: ");
        fgets(buffer, 100, stdin);
        //get 2nd
        int sec_num = atoi(buffer);

        //divisor
        int result = first_num / sec_num;
        //remainder
        int remainder = first_num % sec_num;

        printf(" %i / %i is %i with a remainder of %i\n", first_num, sec_num, result, remainder);
        division_count++;

    
    
    }
    return(0);

}
