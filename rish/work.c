#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "rish.h"

#define BUFSIZE 64

char *argvector[BUFSIZE];
char *searchpath[BUFSIZE];

void error(void);

int
cd(void)
{
	if (chdir(argvector[1]) == -1) {
		error();
		return -1;
	} else
		return 0;
}

int
path(void)
{
	char **pav = argvector;
	char **psp = searchpath;

	while ((*psp++ = *++pav))
		;
	return 0;
}

int
builtin()
{
	if (strcmp(argvector[0], "cd") == 0) 
		return 1;
	else if (strcmp(argvector[0], "path") == 0)
		return 2;
	else if (strcmp(argvector[0], "exit") == 0)
		return 3;
	else
		return 4;
}

int
lexer(char *s)
{
	char **ap;
	char **p = argvector;
	int count = 0;


	for (ap = argvector; ap < &argvector[BUFSIZE] &&
	    (*ap = strsep(&s, " ")) != NULL;) {
		if (**ap != '\0') {
			++count;
			++ap;
		}
	}
	*ap = NULL;
	return count;
}

void
error(void)
{
	char *error_message = "An error has occurred\n";
    	write(STDERR_FILENO, error_message, strlen(error_message)); 
}


int
execute(void)
{
	char p[32] = "/bin/";
	strlcat(p, argvector[0], sizeof(p));

	if (access(p, X_OK) == -1) {
		error();
		return -1;
	}
	
	char *a[] = {argvector[0], argvector[1], argvector[2], NULL};
	int rc;

	if ((rc = fork()) == -1)
		error();
	else if (rc == 0)
		execv(p, a);
	else 
		wait(NULL);
	
	return 0;
}
