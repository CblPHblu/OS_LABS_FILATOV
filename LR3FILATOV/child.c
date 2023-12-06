#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "stddef.h"
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MEMORY_NAME "LR3FILATOV"
#define DATA_SIZE 256   // Больше значений и не надо
#define MEMORY_SIZE 8192    // С лихвой хватит памяти. Вы что там считать собрались?

void check_error(bool expression, char* message) {  // Покажи, чего там снова не получается
    if (expression) {
        write(STDOUT_FILENO, message, strlen(message) * sizeof(char));
        write(STDOUT_FILENO, "\n", 1);
        exit(-1);
    }
}

typedef struct {    // Нам и размер нужен, и массив под результат!
    size_t size;
    int data[DATA_SIZE];
} res;

int main() {
    int fd = shm_open(MEMORY_NAME, O_EXCL | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);   // Разделяем память (подключаемся к нашему любимчику родителю)
    check_error(fd == -1, "Can't open shared memory file"); // Что-то пошло не так???
    if (ftruncate(fd, MEMORY_SIZE) == -1) {    // ТЫ ЧЕГО СЧИТАТЬ СОБРАЛСЯ? БУКВЫ В "ВОЙНЕ И МИРЕ"?!
        printf("File is too large");
    }
    res *addr = mmap(NULL, MEMORY_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);    // А теперь работаем с файликом, как с памятью!!!
    check_error(addr == (void*)-1, "Mmap error");   // НУ СКОЛЬКО МОЖНО!
    addr->size = 0;    // Ну пока нету там ничего, падажжи

    char c;
    bool not_end = true;
    int nmbr = 0;
    int result = 0;
    int count = 0;
    int numbers[100];

    do {
        if (not_end) {
            if (c <= '9' && c >= '0') {
                nmbr = nmbr * 10 + c - '0';
            }
            if (c == ' ' || c == '\n' || c == EOF) {
                numbers[count] = nmbr;
                nmbr = 0;
                count++;
                if (c == '\n' || c == EOF) {
                    for (int i = 0; i < count; i++) {
                        result = result + numbers[i];
                    }
                    not_end = false;
                    count = 0;
                }
            }
        }
        if (c == '\n' || c == EOF) {
            addr->data[addr->size++] = result;
            result = 0;
            not_end = true;
        }
    } while((scanf("%c", &c)) > 0);

    return 0;
}