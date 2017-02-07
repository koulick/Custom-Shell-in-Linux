/* CS 5348 Fall 2016 - Project 1 */
/* Team Members: Manisha Arumugam (mxa165730@utdallas.edu) and Koulick Sankar Paul (ksp160330@utdallas.edu) */
/* Connect to csgrads1.utdallas.edu using the putty program or ssh */
/* Program Name: myshell.c */
/* Compile using 'cc myshell.c' and execute using './a.out' */

/* The program executes in a loop (until user types exit on the keyboard), */
/* prints a prompt on the screen, */
/* reads the command typed on the keyboard (terminated by \n), */
/* creates a new process and lets the child execute the user’s command, */
/* waits for the child to terminate and then goes back to beginning of the loop. */
/* If the command typed is exit, then it terminates. */
/* The program prints the total number of commands executed just before terminating. */

#include  <stdio.h>
#include  <sys/types.h>
#include  <stdlib.h>

void parseInput(char*, char** );
void executeCommand(char** );

/* Main Function */
int main() {
        char inputLine[100];
        char *argument[64];
        int noOfCommands = 0;

        while (1) {
                /* print a prompt on the screen and wait for the user input */
                write(1, "Type the command you want: ", 27);
                gets(inputLine);

                /* increment the number of commands entered */
                noOfCommands+=1;

                /* parse the input into arguments */
                parseInput(inputLine, argument);

                /* if the argument typed is 'exit' */
                if (strcmp(argument[0], "exit") == 0) {
                        printf("No. of commands executed is: %d\n",noOfCommands);
                        exit(0);
                }

                /* otherwise, execute the typed command */
                executeCommand(argument);
        }
}

/* FUNCTION Name: parseInput */
/* This function takes an input line and parses it into individual arguments. */
/* It first replaces all white spaces with NULL('\0'), */
/* until it hits a non-white space character which indicates the beginning of an argument. */
/* It saves the address to args[], and then skips all non-white spaces which constitute the argument. */
void  parseInput(char *line, char **args) {
        while (*line != '\0') {
                /* strip the whitespaces. */
                /* use '\0' so that the previous argument is terminated automatically */
                while (*line == ' ' || *line == '\t' || *line == '\n')
                        *line++ = '\0';

                /* save the argument position */
                *args++ = line;

                /* skip over the argument */
                while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n')
                        line++;
                }

                /* mark the end of argument list  */
                *args = '\0';
}

/* FUNCTION Name: executeCommand */
/* This function receives a command line argument list with the first one being a file name followed by its arguments. */
/* It forks a child process, which in turn executes the command using system call execvp(). */
void  executeCommand(char **args) {
        int pid, status;
        if ((pid = fork()) < 0) {
                write(1, "Forking child process failed! The error is given below:\n", 56);
                perror("fork");
                exit(1);
                }
        /* child executes the code here */
        else if (pid == 0) {
                /* execute the command  */
                if (execvp(*args, args) < 0) {
                        write(1, "Exec failed! The error is given below:\n", 39);
                        perror(*args);
                        exit(1);
                        }
		}
                /* parent executes the wait for completion  */
                else {
                        while (wait(&status) != pid)
                                /* empty */ ;
                }
}
