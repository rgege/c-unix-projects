#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 1000

struct nlist {
	struct nlist *next;
	char *key;
	char *value;
};

static struct nlist *hashtab[HASHSIZE];

unsigned 
hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 *hashval;
	return hashval % HASHSIZE;
}

struct nlist *
lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->key) == 0)
			return np;
	return NULL;
}

void
get(char *k)
{
	struct nlist *np;

	if ((np = lookup(k)) == NULL)
		fprintf(stderr, "%s not found\n", k);
	else
		fprintf(stdout, "%s,%s\n", np->key, np->value);
}
		
	

struct nlist *
install(char *k, char *v)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(k)) == NULL) {

		np = malloc(sizeof(*np));
		if (np == NULL || (np->key = strdup(k)) == NULL)
			return NULL;
		hashval = hash(k);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else
		free(np->value);
	if ((np->value = strdup(v)) == NULL)
		return NULL;
	return np;
}

void
delete(char *k)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(k)) == NULL) {
		fprintf(stderr, "%s not found\n", k);
		exit(1);
	} else {
		hashval = hash(np->key);
		hashtab[hashval] = NULL;
		free(np);
		printf("entry removed\n");
	}
}

int
builddb(void)
{
	FILE *f;
       	if ((f = fopen("database.txt", "r")) == NULL) {
                fprintf(stderr, "no such file\n");
                exit(1);
         }
	
	char line[25];
	char *token, *p = line;

        while ((fgets(line, sizeof(line), f)) != NULL) {
		if (*p != '\n') {
			line[strcspn(line, "\n")] = '\0';
                	token = strsep(&p, ",");
                	install(token, p);
			p = line;
		}
        }
    
        return 0;
}

int
savedb(void)
{
	FILE *f;

	if ((f = fopen("database.txt", "w")) == NULL) {
		fprintf(stderr, "no such file\n");
		exit(1);
	}

	for (int i = 0; i < HASHSIZE; ++i)
		if (hashtab[i] != NULL)
			if ((fprintf(f, "%s,%s\n", 
				hashtab[i]->key, 
				hashtab[i]->value)) == -1)
					fprintf(stderr, "error\n");
	fclose(f);
	return 0;
}


void
printdb(void)
{
	for (int i = 0; i < HASHSIZE; ++i) 
		if (hashtab[i] != NULL) 
			printf("%s,%s\n", hashtab[i]->key, 
			          	  hashtab[i]->value);
}

void
cleardb(void)
{
	for (int i = 0; i < HASHSIZE; ++i) 
		if (hashtab[i] != NULL)
			hashtab[i] = NULL;
	fprintf(stdout, "database cleared\n");
}
