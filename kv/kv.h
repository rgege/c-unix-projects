struct nlist *parseline(char *);
struct nlist *install(char *, char*);

void delete(char *);
void get(char *);

int builddb(void);
int savedb(void);
void printdb(void);
void cleardb(void);
