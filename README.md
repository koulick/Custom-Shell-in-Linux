Implements Custom Shell in Linux:

It executes in a loop (until user types exit on the keyboard), prints a prompt on the screen, reads the command typed on the keyboard (terminated by \n), creates a new process and lets the child execute the user’s command, waits for the child to terminate and then goes back to beginning of the loop.

If the command typed is exit, then the program terminates.

The program prints the total number of commands executed just before terminating.
