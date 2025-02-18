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

int main(int argc, char** argv){
    initialize_heap();
}



