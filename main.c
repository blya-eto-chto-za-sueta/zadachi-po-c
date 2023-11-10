#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(){
    FILE* fin = fopen("input.txt","rb");
    freopen("output.txt", "w", stdout);
    int32_t N;// количество байтов в файле
    fread(&N,sizeof (int32_t),1,fin);
    int32_t countBites=4;// количество считанных байтов

    printf("{\n");
    while(countBites<N){
        int8_t T;
        fread(&T,sizeof (int8_t),1,fin);
        countBites++;
        switch (T){
            case 1 :{//  значение типа double
                char* fieldName=(char*)malloc(sizeof (char)*1000);

                fieldName[0]=1;// чтобы зайти в изначальный цикл
                int32_t idx=0;

                while (fieldName[idx]!=0){ // проверяем последний записанный байт
                    if (idx==0){
                        idx--;
                    }// чтобы запись началась с 0
                    idx++;
                    fread(&fieldName[idx],sizeof(char),1,fin);
                    countBites++;
                }// посимвольная запись имя поля

                double meaning;
                fread(&meaning,sizeof(double),1,fin);
                countBites+=8;

                printf("\t");
                printf("\"");
                for (int i=0;i<idx;i++){
                    printf("%c",fieldName[i]);
                }
                printf("\"");
                printf(":");
                printf(" ");
                printf("%0.15g",meaning);

                if (countBites<N){
                    printf(",");
                }
                printf("\n");
                break;
            }
            case 2 :{// string
                char* fieldName=(char*)malloc(sizeof (char)*1000);

                fieldName[0]=1;// чтобы зайти в изначальный цикл
                int32_t idx=0;

                while (fieldName[idx]!=0){ // проверяем последний записанный байт
                    if (idx==0){
                        idx--;
                    }// чтобы запись началась с 0
                    idx++;
                    fread(&fieldName[idx],sizeof(char),1,fin);
                    countBites++;
                }// посимвольная запись имя поля

                int32_t L;// равно количеству байтов в строке, включая дополнительный нулевой байт.
                fread(&L,sizeof (int32_t),1,fin);
                countBites+=4;

                char* string=(char*)malloc(sizeof (char)*L);
                fread(string,sizeof (char),L,fin);
                countBites+=L;

                printf("\t");
                printf("\"");
                for (int i=0;i<idx;i++){
                    printf("%c",fieldName[i]);
                }
                printf("\"");
                printf(":");
                printf(" ");
                printf("%s",string);

                if (countBites<N){
                    printf(",");
                }
                printf("\n");
                break;
            }
            case 8 :{ //bool
                char* fieldName=(char*)malloc(sizeof (char)*1000);

                fieldName[0]=1;// чтобы зайти в изначальный цикл
                int32_t idx=0;

                while (fieldName[idx]!=0){ // проверяем последний записанный байт
                    if (idx==0){
                        idx--;
                    }// чтобы запись началась с 0
                    idx++;
                    fread(&fieldName[idx],sizeof(char),1,fin);
                    countBites++;


                }// посимвольная запись имя поля

                char isBoll;
                fread(&isBoll,sizeof (char),1,fin);
                countBites++;

                printf("\t");
                printf("\"");
                for (int i=0;i<idx;i++){
                    printf("%c",fieldName[i]);
                }
                printf("\"");
                printf(":");
                printf(" ");
                printf("%d",isBoll);

                if (countBites<N){
                    printf(",");
                }
                printf("\n");
            }
            case 10: {//значение типа null.
                char* fieldName=(char*)malloc(sizeof (char)*1000);

                fieldName[0]=1;// чтобы зайти в изначальный цикл
                int32_t idx=0;

                while (fieldName[idx]!=0){ // проверяем последний записанный байт
                    if (idx==0){
                        idx--;
                    }// чтобы запись началась с 0
                    idx++;
                    fread(&fieldName[idx],sizeof(char),1,fin);
                    countBites++;


                }// посимвольная запись имя поля

                printf("\t");
                printf("\"");
                for (int i=0;i<idx;i++){
                    printf("%c",fieldName[i]);
                }
                printf("\"");
                printf(":");
                printf(" ");
                printf("null");

                if (countBites<N){
                    printf(",");
                }
                printf("\n");

            }
            case 16: {//значение типа int32
                char* fieldName=(char*)malloc(sizeof (char)*1000);

                fieldName[0]=1;// чтобы зайти в изначальный цикл
                int32_t idx=0;

                while (fieldName[idx]!=0){ // проверяем последний записанный байт
                    if (idx==0){
                        idx--;
                    }// чтобы запись началась с 0
                    idx++;
                    fread(&fieldName[idx],sizeof(char),1,fin);
                    countBites++;


                }// посимвольная запись имя поля
                int32_t meaning;
                fread(&meaning,sizeof(int32_t),1,fin);
                countBites+=4;

                printf("\t");
                printf("\"");
                for (int i=0;i<idx;i++){
                    printf("%c",fieldName[i]);
                }
                printf("\"");
                printf(":");
                printf(" ");
                printf("%d",meaning);

                if (countBites<N){
                    printf(",");
                }
                printf("\n");

            }

            case 18: {//значение типа int64
                char* fieldName=(char*)malloc(sizeof (char)*1000);

                fieldName[0]=1;// чтобы зайти в изначальный цикл
                int32_t idx=0;

                while (fieldName[idx]!=0){ // проверяем последний записанный байт
                    if (idx==0){
                        idx--;
                    }// чтобы запись началась с 0
                    idx++;
                    fread(&fieldName[idx],sizeof(char),1,fin);
                    countBites++;


                }// посимвольная запись имя поля
                int64_t meaning;
                fread(&meaning,sizeof(int64_t),1,fin);
                countBites+=8;

                printf("\t");
                printf("\"");
                for (int i=0;i<idx;i++){
                    printf("%c",fieldName[i]);
                }
                printf("\"");
                printf(":");
                printf(" ");
                printf("%d",meaning);

                if (countBites<N){
                    printf(",");
                }
                printf("\n");

            }

        }

    }
    printf("\n}");
    printf("%d",countBites);
    fclose(fin);
}