/*
Author: Joaquim Costa
Date: Oct. 01, 2011
Operating Systems (cs435)

word.c - this is a simple program that demostrates the usage of pipe in the linux system.
this program creates two child process. these child process exec two short program:
reverse - simple reverses the string passed as the argument
switchcase - simple switches the case of the of the alphabet.

the reverse & switchcase can also be used separatly example

./reverse "**I love programming**"
./switchcase "ric IS UPPERCASE"

the word program is used as this:
./world "this is will be reverse and uppercase!"

The word program utilizes these two programs to manipulate the string.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

const int READ_END = 0;		// for the read descriptor
const int WRITE_END = 1;	// for the write descriptor

int main(int argc, char *argv[])
{
    // display program usage
    if( (argc != 2) || strcmp(argv[1], "--help") == 0)
    {
        printf("%s string - enclose the string to be processed, in quote\n", argv[0]);
        return -1;
    }

    char* buffer;
    int bufferSize = strlen(argv[1]) +1;

    // allocated memory for the buffer holder
    buffer = (char*) malloc(bufferSize);

    // pipe file decriptor
    int fd[2];

    // create pipe
    pipe(fd);

    switch (fork())
    {
    case -1:
        printf("fork error");
        return -1;

    case 0:// code for the first child
        close(fd[READ_END]);

        //duplicate stdout on write-end
        dup2(fd[WRITE_END], STDOUT_FILENO);
        close(fd[WRITE_END]);

        // writes to pipe
        execlp("./switchcase", "./switchcase", argv[1], NULL);


    default: // parend section do nothing
        break;
    }

    // create another process
    switch (fork())
    {
    case -1:
        printf("fork error");
        return -1;

    case 0: // code for the second child
        close(fd[WRITE_END]); // write-end is unused

        //duplicate stdin on read-end
        dup2(fd[READ_END], STDIN_FILENO);
        close(fd[READ_END]);

        // read buffer from stdio
        read(STDIN_FILENO, buffer, bufferSize );

        execlp("./reverse", "./reverse", buffer, NULL);



    default:// code for the parent

        /* close unused file decriptors and wait for childrens */
        //close(fd[READ_END]);
        close(fd[WRITE_END]);

        // wait for first child signal
        wait();

        // wait for second child signal
        wait();
        break;
    }


    return 0;
}
