////////////////////////////////////////////////////////////////////////////////
// Main File:        my_c_signal_handler.c
// This File:        my_c_signal_handler.c
// Other Files:      send_signal.c
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
// Online sources:   https://stackoverflow.com/questions/1784136/simple-signals-c-programming-and-alarm-function
// ^ this helped with the format and helped understand how I was supposed to structure the handlers for alarms
// Class Notes also helped in that 
// this also helped with understanding alarm calls : 
// https://stackoverflow.com/questions/12406915/using-signal-and-alarm-as-timeouts-in-c
// 
// 
// AI chats:         save a transcript and submit with project.
//////////////////////////// 80 columns wide ///////////////////////////////////
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

//easier to decl 5 sec here
int alarm_time = 5;
//new- SIGUSR1
int sigusr1count = 0;

void handle_SIGALRM(){
    //pid_t pid = getpid(); - wrong
    time_t currentTime;
    //time(&currentTime); - wrong

    //Check if the curr time valid
    if(time(&currentTime) == -1){
        printf("Error on current time");
        exit(0);
    }

    //Print PID and time every 5 sec
    printf("PID: %d", getpid());
    printf(" CURRENT TIME: %s", ctime(&currentTime));

    //Check if alarm timer is off
    if(alarm(alarm_time) != 0){
        printf("Error alarm timer");
        exit(0);
    }
    //reset to 5 sec
//    alarm(alarm_time);
}

/*
Extend your implementation of my_c_signal_handler.c 
so that it prints a message on receiving a SIGUSR1 signal. 
It should also increment a global counter to keep tally of 
the number of times it receives SIGUSR1. To achieve this, 
you will need to write another signal handler and register 
it to handle the SIGUSR1 signal using sigaction() one more time.
*/
void handler_SIGUSR1(){
    printf("SIGUSR1 handled and counted!\n");
    //update count when caught
    sigusr1count++;
}

/*
After SIGUSR1 goes and we end the program with the command ctrl+c
we have to print out that sigint was handled and display how many times
sigusr1 was handled.
*/
void handler_SIGINT(){
    printf("SIGINT handled.\n");
    printf("SIGUSR1 was handled %i times. Exiting now.\n", sigusr1count);

    exit(0);

}
/*
This will be a signal handler with code to handle 3 signals:
1. a periodic signal from an alarm (set by the code with the alarm timer argument)
2. a keyboard interrupt signal
3. a user defined signal
*/
int main(int argc, char *argv[]){
    // Print instructions to the user
    printf("PID and time print every 5 seconds.\n");
    printf("Type Ctrl-C to end the program.\n");

    //signal for sigalarm
    struct sigaction sigalrm;
    memset(&sigalrm, 0, sizeof(sigalrm));
    sigalrm.sa_handler = handle_SIGALRM;

    //check alarm handle
    if(sigaction(SIGALRM, &sigalrm, NULL) < 0){
        printf("Error for SIGALARM");
        exit(0);
    }

    //check for the global timer
    if(alarm(alarm_time) != 0){
        printf("Alarm error.\n");
        exit(0);
    }

    //SIGUSR1
    struct sigaction sigusr1;
	memset (&sigusr1, 0, sizeof(sigusr1));
    sigusr1.sa_handler = handler_SIGUSR1;


    if(sigaction(SIGUSR1, &sigusr1, NULL) < 0){
        printf("Error SIGUSR1");
        exit(0);

    }

    //SIGINT
    struct sigaction sigint;
	memset (&sigint, 0, sizeof(sigint));
    sigint.sa_handler = handler_SIGINT;

    if(sigaction(SIGINT, &sigint, NULL) < 0){
        printf("Error SIGINT");
        exit(0);

    }

    while(1){
        //infinite loop with no output
    }
    return 0;
}
