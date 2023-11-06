#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kv.h"

int
main(int argc, char *argv[])
{
	if (argc < 2)
		exit(1);

	builddb();

	char *s, *command, *token;
	while (--argc > 0) {
		++argv;
	
		command = strsep(&*argv, ",");
		token = strsep(&*argv, ",");

		switch(command[0]) {
			case 'p':
				install(token, *argv);
				break;
			case 'g':
				get(token);
				break;
			case 'd':
				delete(token);
				break;
			case 'c':
				cleardb();
				break;
			case 'a':
				printdb();
				break;
			default:
				printf("bad command\n");
				break;
		}
	}

	savedb();
	return 0;
}
