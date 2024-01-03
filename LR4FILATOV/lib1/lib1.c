#include "lib1.h"


int GCF(int a, int b){
    while (a != b){
        if (a > b){
            a -= b;
        }
        else{
            b -= a;
        }
    }
    return a;
}

char* translation(long x){
    char* result = (char*)malloc(sizeof(char)); 
    int index = 0;
    
    while(x > 0) {
        result[index] = x % 2 + '0';
        index += 1;
        x /= 2;
        result = realloc(result, (index + 1) * sizeof(char));
    }
    
    result[index] = '\0';
    char symbol;

    for(int permutation_index = 0; permutation_index < index / 2; ++permutation_index) {
        symbol = result[permutation_index];
        result[permutation_index] = result[index - permutation_index - 1];
        result[index - permutation_index - 1] = symbol; 
    }
    
    return result; 
    free(result);
}

//gcc -c -fPIC lib1.c
//gcc -shared lib1.o -o lib1.so -lm