
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mymalloc.h"


//include the three stress tests in (4.0), as well as two of our own
//pretty sure the the firs three can be done with for loops, but we'll have to see

int main(){

    for(int i = 0; i < 120; i++){
        void * ptr = malloc(1);
        free(ptr);
    }

    printf("yippee");
    
    void* arr[120];
    for(int i = 0; i < 120; i++){
        arr[i] = malloc(1);
    }
    for(int i = 0; i < 120; i++){
        free(arr[i]);
    }





    for(int i = 0; i < 120; i++){
        int arrIndex = 0;
        if(rand() % 2 == 0){
            while(arrIndex < 120){
                if(arr[arrIndex] == NULL){ //might be wrong
                    arr[arrIndex] = malloc(1);
                    arrIndex = 0;
                    break;
                }
                arrIndex++;
            }
        }
        else{
            while(arrIndex < 120){
                if(arr[arrIndex] != NULL && *(int *)(arr[arrIndex] - 4) == 1){
                    free(arr[arrIndex]);
                    arrIndex = 0;
                    break;
                }
                arrIndex++;
            }
        }
    }
    for(int i = 0; i < 120; i++){
        if(arr[i] != NULL){
            free(arr[i]);
        }
    }
    return EXIT_SUCCESS;
}