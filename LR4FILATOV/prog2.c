#include <stdio.h>
#include <dlfcn.h>


int main(){
    int check;
    int key = 2;
    int result1;
    char* result2;
    int arg1, arg2;
    long arg3;
    void *current_lib;
    current_lib = dlopen("./lib2/lib2.so", RTLD_LAZY); // Загрузка библиотеки

    if (!current_lib) {
        printf("Library loading error\n");
        return 1;
    }

    int (*GCF)(int, int) = dlsym(current_lib, "GCF"); // Получение указателя на функцию
    char* (*translation)(long) = dlsym(current_lib, "translation");
    if (!GCF) {
        printf("Could not find function\n");
        return 1;
    }

    while(scanf("%d", &check) != EOF){
        if (check != 0 && check != 1 && check != 2){
            printf("Wrong argument\n");
            dlclose(current_lib); // Закрытие библиотеки
            return 1;
        }
        else if(check == 1){
            scanf("%d %d", &arg1, &arg2);
            result1 = GCF(arg1, arg2);
            printf("NOD is: %d\n", result1);
        }
        else if(check == 2){
            scanf("%ld", &arg3);
            result2 = translation(arg3);
            printf("From 10 to 3 system: %s\n", result2);
        }
        else if(check == 0){
            if (key == 2){
                current_lib = dlopen("./lib1/lib1.so", RTLD_LAZY); 
                key = 1;
            }
            else{
                current_lib = dlopen("./lib2/lib2.so", RTLD_LAZY); 
                key = 2;
            }

            if (!current_lib) {
                printf("Library loading error\n");
                return 1;
            }

            GCF = dlsym(current_lib, "GCF");
            translation = dlsym(current_lib, "translaton");
        }   
    }
    dlclose(current_lib); 
    return 0;
}