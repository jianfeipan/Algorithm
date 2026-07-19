typedef struct {
    int a;
    int b;
} datatype;

void alloc(datatype* ptr) {
    ptr = malloc(sizeof(ptr));
    ptr->a = 10;
    ptr->b = 20;
}

int main() {
    datatype * ptr = NULL;
    alloc(ptr);
    printf(ptr->a);
}


#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} datatype;

void alloc(datatype** ptr) {
    // 1. Use the size of the struct, not the size of the pointer
    *ptr = malloc(sizeof(datatype)); 
    
    // 2. Dereference once to access the struct members
    (*ptr)->a = 10;
    (*ptr)->b = 20;
}

int main() {
    datatype *ptr = NULL;
    alloc(&ptr); // Pass the address of the pointer
    
    if (ptr != NULL) {
        printf("%d\n", ptr->a);
        free(ptr); // Don't forget to clean up!
    }
    return 0;
}