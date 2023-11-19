#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef UTEST_STRING
        #define UTEST_STRING ""
#endif

char *
mgets(char *s)
{
	char *tstr = UTEST_STRING;

	if (*tstr == '\0') {
		return fgets(s, sizeof(s), stdin);
	} else {
		strlcpy(s, tstr, sizeof(s));
		return s;
	}
}


char *
getinput(char *s) 
{
        printf("rish$> ");
        if (mgets(s) == NULL) {
                printf("\n");
                exit(0);
	} else if (strcmp(s, "\n") == 0) {
		return s;
	} else {
                s[strcspn(s, "\n")] = '\0';
	}
        
        return s;
}
