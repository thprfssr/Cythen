#include <stdio.h>
#include "parser.h"

char *file_to_string(char *filename)
{
	FILE *file;
	char *buffer;
	long bytes;

	/* Open file */
	file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Could not open file!\n");
		exit(-1);
	}

	/* Get the number of bytes */
	fseek(file, 0L, SEEK_END);
	bytes = ftell(file);

	/* Reset the file position indicator */
	fseek(file, 0L, SEEK_SET);

	/* Allocate memory */
	buffer = (char *) malloc(bytes * sizeof(char));
	if(buffer == NULL)
	{
		printf("Could not allocate memory!\n");
		exit(-1);
	}

	/* Copy all the text into the buffer */
	fread(buffer, sizeof(char), bytes, file);
	fclose(file);

	/* NOTE: I am pretty sure this will cause a memory leak, since we're
	 * not freeing the memory allocated for the buffer.
	 */

	return buffer;
}

/* We need this function in order to obtain the layout of the tilemap.
 * What the function does is take a string as an input, and it tokenizes it
 * with whitespace, newline, and tab as delimiters. In the end, it returns
 * an array of strings.
 */
char **parse_text(char *text)
{
	char **buffer = NULL;
	char *delimiters = " \n\t";
	for(int i = 0; ; i++)
	{
		char *tmp;
		tmp = strtok(text, delimiters);
		if (tmp == NULL)
		{
			break;
		}
		else
		{
			**buffer = (char **)realloc(**buffer, sizeof(tmp));
			buffer[i] = tmp;
			printf("%s\n", tmp);
		}
	}
}
