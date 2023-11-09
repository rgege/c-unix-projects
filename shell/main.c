#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 32

char *
getinput(char *s)
{
	printf("rish$> ");
	if (fgets(s, sizeof(s), stdin) == NULL)	
		exit(1);
	else
		s[strcspn(s, "\n")] = '\0';
	return s;
}

int
main(int argc, char *argv[])
{
	const char *ex = "exit";

	char buf[BUFSIZE];
	int c;

	while ((c = strcmp(getinput(buf), ex))) {

	}

	return 0;
}
