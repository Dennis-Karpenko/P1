//This should remain as is, with no changes. This is not where we write mymalloc and free, my bad.
#define malloc(X) mymalloc(X, __FILE__, __LINE__)
#define free(X) myfree(X, __FILE__, __LINE__)
void * mymalloc(size_t, char *, int);
void myfree(void *, char *, int);


