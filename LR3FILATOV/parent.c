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

#define MEMORY_NAME "LR3FILATOV"
#define DATA_SIZE 256    // Больше значений и не надо
#define MEMORY_SIZE 8192    // С лихвой хватит памяти. Вы что там считать собрались?

void check_error(bool expression, char* message) {      // Покажи, чего там снова не получается
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

int main (int argc, char* argv[]) {
    pid_t pid;      // Создай-ка процесс
    FILE *fp = NULL;
    if (argc != 2) {    // Ну ты чего, надо же написать что-то после вызова программы!
        write(1, "Wrong arguments\n", 17);
        exit(EXIT_FAILURE);
    }
    pid = fork();       // Дочернего привести сюда не-ме-дле-нно!
    if (pid == -1) {    // Не привели?? Что случилось, кто посмеял?
        perror("fork");
        return -1;
    }
    else if (pid == 0) {    // Ну наконец-то. Что тут у нас?
        fp = freopen(argv[1], "r", stdin);  // Откройте букву "ФАЙЛ"
        check_error(fp == NULL, "Can't open file"); // Нет такой буквы!
        execl("./child", "/.child", NULL);  // Запустить другую программу из текущей
        perror("execl");
        return 1;
    }
    else {  // Родитель? К тебе есть пару вопросов...
        wait(0);    // Ну погоди, погоди, щас отработает Детишко
        int fd = shm_open(MEMORY_NAME, O_RDONLY, S_IRUSR | S_IWUSR);    // Разделяем память!!!
        check_error(fd == -1, "Can't open shared memory file"); // Что-то пошло не так???
        res *addr = mmap(NULL, MEMORY_SIZE, PROT_READ, MAP_SHARED, fd, 0);  // А теперь работаем с файликом, как с памятью!!!
        check_error(addr == (void*) -1, "Mmap error");  // НУ СКОЛЬКО МОЖНО!
        for (int i = 0; i < addr->size; i++) {  // Покажи, чего там получилось у Детишко?
            printf("Сумма цифр в %d строке: %d\n", i + 1, addr->data[i]);
        }
        printf("Рассчет окончен!\n");
        munmap(addr, MEMORY_SIZE);  // Все, молодец, закрывай всё подряд
        shm_unlink(MEMORY_NAME);
        close(fd);
    }
    
    return 0;
}