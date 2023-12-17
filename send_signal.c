////////////////////////////////////////////////////////////////////////////////
// Main File:        my_c_signal_handler.c
// This File:        send_signal.c
// Other Files:      
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
// Persons:         n/a
//
// Online sources:   n/a
// 
// AI chats:         save a transcript and submit with project.
//////////////////////////// 80 columns wide ///////////////////////////////////
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*
 * This is geenrated for SIGUSR1 where we're gonna take the commands and
 send a signal from another terminal when my_c_signal_handler is running
 */
int main(int argc, char* argv[]) {
    //check with alarm
    if (argc != 3) {  
        printf("Usage: <signal type> <pid>\n");
        exit(0);
    }
    // Getprocess ID 
    pid_t pid = atoi(argv[2]);
    
    //THis is for comparison
    int sigusr1comp = strcmp(argv[1], "-u");
    int sigintcomp = strcmp(argv[1], "-i");

    if (sigusr1comp == 0) { 
        if (kill(pid, SIGUSR1) == -1) {
            perror("ERROR on sigusrcomp");
            exit(0);
        }
    } else if (sigintcomp == 0) {  // When the type is -i
        if (kill(pid, SIGINT) ==-1) {
            printf("ERROR on sigintcomp");
            exit(0);
        }
    } else {  
        //if not any then signal is just wrong
        printf("wrong signal");
        exit(0);
    }
    return 0;
}
