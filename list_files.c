#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

//--------------------------------------------------------------------------------------------------------------------//

void show(const char *name, int level)
{
	DIR *dir;
	struct dirent *source;

	if(NULL == (dir = opendir(name)) )
		return;
	if(NULL == (source = readdir(dir)) )
		return;

	do
	{
		if(source -> d_type == DT_DIR)
		{
			if( strcmp(source -> d_name, ".") == 0 || strcmp(source -> d_name, "..") == 0)
				continue;
			
			int length;

			char path[1000];

			if( name[strlen(name) - 1] != '/')
					length = snprintf(path, sizeof(path) - 1, "%s/%s", name, source -> d_name);
				else
					length = snprintf(path, sizeof(path) - 1, "/%s", source -> d_name);
					// corner case for /

			path[length] = 0;

			printf("%*s- %s\n", level * 2, "", source -> d_name);

			show(path, level + 1);
		}
		else
			printf("%*s-> %s\n", level * 2, "", source -> d_name);

	} while(source = readdir(dir));

	closedir(dir);
}

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		fprintf(stderr, "\nError. Usage: %s directory\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	show(argv[1], 0);

	exit(EXIT_SUCCESS);
}
