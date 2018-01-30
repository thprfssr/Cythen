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

char ***parse_text(char *text)
{
	
}
