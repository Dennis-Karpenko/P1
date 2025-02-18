#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMLENGTH 4096

static int isInitialized = 0;
//static int header_size. tbd later.

static void leak_detector(){
    //something
}

static void initialize_heap(){
    atexit(leak_detector);
    //malloc(4096 - size_of header); 
    isInitialized = 1;
}
static union {
    char bytes[MEMLENGTH];
    double not_used;
} heap;

struct {
    int size;
    int is_free;
} header;

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



