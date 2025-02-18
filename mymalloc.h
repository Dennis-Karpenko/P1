#define malloc(X) mymalloc(X, __FILE__, __LINE__)
#define free(X) myfree(X, __FILE__, __LINE__)




void * mymalloc(size_t, char *, int){
//the char array is a source file name, and the int is the line number (section 2). used for error reporting
//make of everything a multiple of 8 using (size + 7) & ~7
//include error detection as in 2.1
    if(!isInitialized){
        initialize_heap();
    }
    //in here, create a new struct
    update chunkheader16 location

}
void myfree(void *, char *, int){
//include error detection as in 2.1
jump to (chunkheader16.location) location, then free it
//make a while loop that coalesces any free blocks
//implementation may be slower, but will have less errors.
}

