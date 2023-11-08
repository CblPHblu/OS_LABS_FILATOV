#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define buf_size 100

int main() {
    int c;
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
            write(STDOUT_FILENO, &result, sizeof(result));
            result = 0;
            not_end = true;
        }
    } while((read(STDIN_FILENO, &c, sizeof(char))) > 0);

    return 0;
}