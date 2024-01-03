#include <stdio.h>
#include "lib1/lib1.h"

int main(){
    int check;
    while(scanf("%d", &check) != EOF){
        if (check != 0 && check != 1 && check != 2){
            printf("Wrong argument\n");
            return 1;
        }
        else if(check == 1){
            int arg1, arg2;
            scanf("%d %d", &arg1, &arg2);
            int result1 = GCF(arg1, arg2);
            printf("NOD is: %d\n", result1);
        }
        else if(check == 2){
            long arg3;
            scanf("%ld", &arg3);
            char* result2 = translation(arg3);
            printf("From 10 to 2 system: %s\n", result2);
        }
        else{
            printf("See you again!\n");
            return 0;
        }   
    }
    return 0;
}
//gcc -o prog1 program1.c lib1/lib1.c -lm