# Signal-Handling
I created an alarm that would snooze every 5 seconds and sent signals from another linux window to handle and count it each time. 
The my_c_signal_handler.c file is a signal handler with code to handle three different types of signals:
1. a periodic signal from an alarm (set by the code with the alarm timer argument)
2. a keyboard interrupt signal
3. a user defined signal
The send_signal.c is used to send signals to other programs including sending signals to the running my_c_signal_handler.
I also did a third program where I add an exception handler that handles divide by 0 exceptions.
my_div0_handler.c does the following:
1. Prompt for and read in one integer value.
2. Prompt for and read in a second integer value.
3. Calculate the quotient and remainder of doing the integer division operation: int1 / int2
4. Print the results as shown in the examples that follow.
5. Keep a total count of how many division operations were successfully completed.
