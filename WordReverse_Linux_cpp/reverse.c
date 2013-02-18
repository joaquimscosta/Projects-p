/*
Author: Joaquim Costa
This program simple take a string as a arguments
and echoes that string in reverse order
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int main(int argc, char* argv[] )
{
    char* text;
    char* reverseText;

    // display program usage
    if( (argc != 2) || strcmp(argv[1], "--help") == 0)
    {
        printf("%s \"string\" - some text enclose in quote\n", argv[0]);
        return -1;
    }

    // assign the text entered by the user
    text = argv[1];

    // reverse the order of the string characters
    int i = strlen(text) -1; // character iterator
    int ireverse = 0;

	// allocate buffer to hold the string in reverse order
    reverseText = (char*) malloc(i+1);

    if(!reverseText) return -1;

    while(i >= 0)
    {

    	// assign last characters to first characters in reverseText
        reverseText[ireverse] = text[i];

		// iterate
        i--;
        ireverse++;
    }

    printf("%s\n",reverseText );

	// free memory
    free(reverseText);


    return 0;
}

