#include "lib2.h"

int GCF(int a, int b){
    int min;
    int result = 1;
    if (a < b) min = a;
    else if (a > b) min = b;
    else return a;
    for (int i = 2; i <= min; i++){
        if ((a % i == 0) & (b % i == 0)){
            result = i;
        }
    }
    return result;
}

char* translation(long x){
    char* result = (char*)malloc(sizeof(char)); 
    int index = 0;
    
    while(x > 0) {
        result[index] = x % 3 + '0';
        index += 1;
        x /= 3;
        result = realloc(result, (index + 1) * sizeof(char));
    }
    
    result[index] = '\0';
    char symbol;

    for(int permutation_index = 0; permutation_index < index / 3; ++permutation_index) {
        symbol = result[permutation_index];
        result[permutation_index] = result[index - permutation_index - 1];
        result[index - permutation_index - 1] = symbol; 
    }
    
    return result; 
    free(result);
}