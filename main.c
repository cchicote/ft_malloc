#include <stdlib.h>
#include <unistd.h>
#include "includes/malloc.h"
#define M (1024 * 1024) 

void print(char *s) 
{ 
    write(1, s, strlen(s)); 
} 

int main() 
{ 
    show_alloc_mem();
    return (0); 
} 
