#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 32

char *argvector[BUFSIZE];

void error(void);

void
cd(char *s)
{
	return 
}

int
builtin(void)
{
	if (strcmp(argvector[0], "cd") == 0)
		return 1;
	else if (strcmp(argvector[0], "path") == 0)
		return 2;
	else if (strcmp(argvector[0], "ls") == 0)
		return 3;
	else
		return -1;
}

void
lexer(char *s)
{
	char **ap;
	char **p = argvector;


	for (ap = argvector; ap < &argvector[9] &&
	    (*ap = strsep(&s, " ")) != NULL;) {
		if (**ap != '\0')
			ap++;
	}
	*ap = NULL;
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
	char buf[BUFSIZE];
	char *p = buf;

	printf("rish$> ");
	if (fgets(buf, sizeof(buf), stdin) == NULL) {
		printf("\n");
		exit(0);
	} else
		buf[strcspn(buf, "\n")] = '\0';
	return p;
}
	
int
main(int argc, char *argv[])
{	
	const char *e = "exit";

	char *s;
	int c;
	char **a;
	
	while (strcmp(s, e)) {
		s = getinput();
		lexer(s);
		c = builtin();

		switch(c) {
			case 1:
				cd(argvector[1]);
				break;
			case 2:
				break;
			case 3:
				system("ls");
				break;
			default:
				break;
		}
	}

	return 0;
}
