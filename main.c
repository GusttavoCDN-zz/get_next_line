#include "get_next_line.h"

#include <stdio.h>
#include <stdlib.h>

void testGnl(char *file_path, char *test_name);

int main(void)
{
	testGnl("./teste.txt", "GNL Example");
}

void testGnl(char *file_path, char *test_name)
{
	FILE *file;
	int i;
	char *current_line;

	printf("----------------------------------------------------------\n");
	printf("-> TEST %s\n", test_name);
	printf("----------------------------------------------------------\n");

	i = 0;
	file = fopen(file_path, "r");

	// to get FD in linux use file->_fileno
	// to get FD in macos use file->_file
	while ((current_line = get_next_line(file->_fileno)) != NULL)
	{
		printf("Line %i : '%s'\n", i, current_line);
		free(current_line);
		i++;
	}

	fclose(file);
	printf("\n");
	printf("\n");
}
