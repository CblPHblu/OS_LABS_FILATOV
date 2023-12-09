#include "stdio.h"
#include "stdlib.h"
#include "bitonic.h"
#include "sys/time.h"

#define MAXINT 2147483647


int SizeStep(int Num){     // Функия нахождения ближайшего числа i, являющегося степенью двойки, для заполнения массива
    int i = 1;
    while(i < Num)
        i *= 2;
    return i;
}


int main(int argc, char *argv[]){
    int threads = 1;    // По умолчанию 1 поток

    if(argc == 2){      // Если пользователь ввёл количество потоков
        threads = atoi(argv[1]); 
    }

    int input_size;     //Вводим количество элементов массива
    scanf("%d",&input_size);

    //находим ближашее число 2^k >= input_size 
    int size_array = SizeStep(input_size); 
    int *array = malloc(sizeof(int)*size_array);
    
    for(int i = 0; i < input_size; ++i)     // Заполняем массив элементами и, в случае необходимости, дополняем "заглушками"
        scanf("%d",array+i);
    for(int i = input_size; i < size_array; ++i)
        array[i] = MAXINT;

    struct timeval start, end;
    gettimeofday(&start, NULL); // получаем время начала выполнения программы

    bitonicsort(array, size_array, threads); 

    gettimeofday(&end, NULL); // получаем время окончания выполнения программы

    bitonicsort(array, size_array, threads);    // Сортируем массив


    for(int i=0;i<input_size;++i){      // Выводим результат
        printf("%d\n",array[i]);
    }

    free(array);    //Освобождаем память

    double elapsed_time = (end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec) / 1000000.0);
    printf("Elapsed time: %.6lf seconds\n", elapsed_time); // выводим время выполнения программы

    return 0;
}