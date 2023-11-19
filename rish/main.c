#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "rish.h"

int
main(void)
{           
        int c;
        char buf[PATH_MAX];
        char *s = ""; 
            
        while (strcmp(s, "exit") != 0) {
                s = getinput(buf);

		if (strcmp(s, "\n") == 0)
			continue;

                lexer(s);
                c = builtin();

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
