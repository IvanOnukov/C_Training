#include <stdio.h>
#include <stdlib.h>

void fileCopy(FILE *, FILE *);

int main(int argc, char *argv[]) {
    FILE *filePoint;
    char *prog = argv[0];
    if (argc == 1) {
        fileCopy(stdin, stdout);
    } else
        while (--argc > 0) {
            if ((filePoint = fopen(*(++argv), "r")) == NULL) {
                fprintf(stderr ,"%s: не могу открыть файл %s\n", prog, *argv);
                exit(1);
            } else {
                fileCopy(filePoint, stdout);
                fclose(filePoint);
            }
        }
    if (ferror(stdout)) {
        fprintf(stderr, "%s: ошибка записи в поток stdout \n", prog);
        exit(2);
    }

    exit(0);
}

void fileCopy(FILE *inFP, FILE *outFP){
    int tmp;
    while ((tmp = getc(inFP)) != EOF){
        putc(tmp, outFP);
    }
}
