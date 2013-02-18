/*
Author: Joaquim Costa
This program simple take a string as a arguments
and echoes that string having opposite characters cases
lowercase to uppercase and uppercase to lowercase
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv[] )
{
    char* text;
    char c;

    // display program usage
    if( (argc != 2) || strcmp(argv[1], "--help") == 0)
    {
        printf("%s \"string\" - some text enclose in quote\n", argv[0]);
        return -1;
    }

    // assign the text entered by the user
    text = argv[1];

    // switch case of the text, (uppercase to lowercase) and (uppercase to lowercase)
    int i = 0; // character iterator
    while(text[i])
    {
        c = text[i];

		// check if character is alphabet
        if( isalpha(c))
        {
            if(islower((int) c))
            {
                c = toupper(c);
            }
            else
            {
                c = tolower(c);
            }

			// swap the character in the string with the opposite case
            text[i] = c;
        }

		// iterate
        i++;
    }

    // echo the user input to the screen
    printf("%s\n", text);

    return 0;
}
