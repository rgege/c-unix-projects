#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>

#define BUFSIZE 32

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
builtin(int c)
{
	if (strcmp(argvector[0], "cd") == 0) {
		if (c != 2) {
			error();
			return -1;
		} else			
			return 1;
	}
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
	char error_message[30] = "An error has occurred\n";
    	write(STDERR_FILENO, error_message, strlen(error_message)); 
}

char *
getinput(void)
{
	char buf[PATH_MAX];
	char *p = buf;

	printf("rish$> ");
	if (fgets(buf, sizeof(buf), stdin) == NULL) {
		printf("\n");
		exit(0);
	} else
		buf[strcspn(buf, "\n")] = '\0';
	return p;
}

void
execute(void)
{
	char s[] = "/bin/";
	char path[PATH_MAX];
	strcpy(path, s);
	printf("%s\n", path);

	char *a[] = {argvector[0], argvector[1], NULL};
	int rc;

	if ((rc = fork()) == -1) 
		error();
	else if (rc == 0)
		execv("bin/ls", a);
	else
		wait(NULL);
}
	
int
main(int argc, char *argv[])
{	
	const char *e = "exit";

	char *s;
	int c;
	int cnt;
	
	while (strcmp(s, e)) {
		s = getinput();
		cnt = lexer(s);
		c = builtin(cnt);

		switch(c) {
			case 1:
				cd();
				break;
			case 2:
				path();
				break;
			case 3:
				exit(0);
				break;
			default:
				execute();
				break;
		}
	}

	return 0;
}
