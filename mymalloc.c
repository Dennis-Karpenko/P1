#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mymalloc.h"

#define MEMLENGTH 4096  // heap memory size - 4096 bytes
int isIni = 0;  // 힙이 초기화되었는지 확인

static union {  // heap 변수 다른 파일에서 직접 접근 불가능, union은 모든 멤버가 같은 메모리 공간을 공유
    char bytes[MEMLENGTH];  // bytes는 4096
    double align;
} heap;

void leak_detector(){
    //int num_bytes = 0;
    int num_objects = 0;
    int location = 0;
    while(location <= 4096){
        if(*(int *)(heap.bytes + location + 4) == 1){
            //num_bytes += *(int *)(heap.bytes + location);
            num_objects++;
            location += *(int *)(heap.bytes + location);
        }
    }
    if(num_objects > 0){
        //printf("mymalloc: %d bytes leaked in %d objects", num_bytes, num_objects);
        printf("mymalloc: %d objects leaked", num_objects);
    }
}

void init_heap() {
        *(int *)(heap.bytes) = 4088;
        *(int *)(heap.bytes + 4) = 0;
        isIni = 1;

        atexit(leak_detector);
}

void *mymalloc(size_t size, char *file, int line) {
    if (!isIni) {
        init_heap();
    }

    size = (size + 7) & ~7;
    int location = 0;

    while(location <= MEMLENGTH - 8) {
        int chunkSize = *(int *)(heap.bytes + location);
        int temp = chunkSize;
        int chunkAllocation = *(int *)(heap.bytes + location + 4);
        if (chunkSize >= size && chunkAllocation == 0) {
            if (chunkSize == size) {
                *(int *)(heap.bytes + location + 4) = 1;
                return (void *)(heap.bytes + location + 8);
            } else {
                *(int *)(heap.bytes + location) = size;
                chunkAllocation = *(int *)(heap.bytes + location + 4) = 1;

                *(int *)(heap.bytes + location + size + 8) = temp - size;
                *(int *)(heap.bytes + location + size + 12) = 0;
                return (void *)(heap.bytes + location + 8);
            }
        }
        location += chunkSize + 8;
    }   
        fprintf(stderr, "malloc: Unable to allocate %zu bytes (%s:%d)\n", size, file, line);
        return NULL;
}

void coalesce(){
    int location = 0;
    while(location < 4096){
        int currentSize = *(int *)(heap.bytes + location);
        int nextSize = *(int *)(heap.bytes + location + currentSize + 8);

        int currentAllocation = *(int *)(heap.bytes + location + 4);
        int nextAllocation = *(int *)(heap.bytes + currentSize + 12);

        if(!currentAllocation && !nextAllocation){
            nextAllocation = 0;
            currentSize += nextSize + 8;

        }
        location += currentSize;
    }
}

void badPointer(void *ptr, char *file, int line) {
    int diff = (char *)heap.bytes - (char *)ptr;
        if (diff < 0 || diff >= MEMLENGTH) {    // condition 1
            printf("free: Inappropriate pointer (%s.c%d)", file, line);
            exit(2);
        } 
        int location = 0;
        while (location < MEMLENGTH) {  // condition 2
            if ((int *)(heap.bytes + location + 8) <= (int *)ptr) {
                if ((int *)(heap.bytes + location + 8) == ptr) {
                    *(int *)(heap.bytes + location - 4) = 0;
                    coalesce();
                } else {
                    location += *(int *)(heap.bytes + location + 4);  
                }
            } else {
                printf("free: Inappropriate pointer (%s.c%d)", file, line);
                exit(2);
            }
        }
        if (*(int *)(ptr - 4) == 0) { // condition 3
            printf("free: Inappropriate pointer (%s.c%d)", file, line);
            exit(2);
            // similiar with condition 2
        }
}

void myfree(void *ptr, char *file, int line) {
    if(!isIni){
        init_heap();
    }
    badPointer(ptr, file, line); 
    coalesce();  
}