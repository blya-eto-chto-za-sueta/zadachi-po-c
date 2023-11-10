#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    FILE *fin = fopen("input.txt", "rb");
    freopen("output.txt", "w", stdout);
    int32_t N;// количество байтов в файле
    fread(&N, sizeof(int32_t), 1, fin);
    int32_t countBites = 5;// количество считанных байтов

    printf("{\n");
    while (countBites < N) {
        int8_t T;
        fread(&T, sizeof(int8_t), 1, fin);
        countBites++;
        // запись и вывод имени поля
        printf("\t");
        printf("\"");

        char tempName=1;
        while (1 == 1) { // проверяем последний записанный байт
            fread(&tempName, sizeof(char), 1, fin);
            if (tempName == 0) {
                countBites++;
                break;
            }
            printf("%c", tempName);
            countBites++;
        }
        printf("\": ");

        switch (T) {
            case 1 : {//  значение типа double
                double meaning;
                fread(&meaning, sizeof(double), 1, fin);
                countBites += 8;

                printf("%0.15g", meaning);

                if (countBites < N) {
                    printf(",");
                }
                printf("\n");
                break;
            }

            case 2 : {// string
                int32_t L;// равно количеству байтов в строке, включая дополнительный нулевой байт.
                fread(&L, sizeof(int32_t), 1, fin);
                countBites += 4;

                char *string = (char *) malloc(sizeof(char) * L);
                fread(string, sizeof(char), L, fin);
                countBites += L;

                printf("\"");
                printf("%s", string);
                printf("\"");
                if (countBites < N) {
                    printf(",");
                }
                printf("\n");
                break;
            }
            case 8 : { //bool
                char isBoll;
                fread(&isBoll, sizeof(char), 1, fin);
                countBites++;

                if (isBoll == 1) {
                    printf("true");
                } else {
                    printf("false");
                }

                if (countBites < N) {
                    printf(",");
                }
                printf("\n");
                break;
            }
            case 10: {//значение типа null.

                printf("null");

                if (countBites < N) {
                    printf(",");
                }
                printf("\n");
                break;
            }
            case 16: {//значение типа int32
                int32_t meaning;
                fread(&meaning, sizeof(int32_t), 1, fin);
                countBites += 4;

                printf("%d", meaning);

                if (countBites < N) {
                    printf(",");
                }
                printf("\n");
                break;
            }
            case 18: {//значение типа int64
                int64_t meaning;
                fread(&meaning, sizeof(int64_t), 1, fin);
                countBites += 8;

                printf("%d",meaning);

                if (countBites < N) {
                    printf(",");
                }
                printf("\n");
                break;
            }
        }
    }
    printf("}");
    fclose(fin);
}
