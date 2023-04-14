#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//для хранения максимального, минимального и их разности среднего балла в группе
typedef struct Group{
    int group;
    double max;
    double min;
    int student;
} Grp;

int main() {
    FILE* fp = fopen("data.csv", "r");
    char data[150];
    char *first;
    first = fgets(data, 150, fp);
    char* line;
    char* tmp;
    Grp mas[150];
    int i = 0;
    while(line = fgets(data, 150, fp)) {
        int count = 0, gr, flag = 1;
        double sum = 0;
        Grp x;
        tmp = strtok(line, ";");
        while(tmp != 0) {
            if(count == 4) gr = atoi(tmp);
            if(count > 4) sum += atoi(tmp);
            tmp = strtok(NULL, ";");
            count++;
        }
        for(int j = 0; j < i; j++) {
            if(mas[j].group == gr) {
                mas[j].student += 1;
                if(mas[j].max < sum / 4) mas[j].max = sum / 4;
                if(mas[j].min > sum / 4) mas[j].min = sum / 4;
                flag = 0;
            }
        }
        if(flag == 1) {
            mas[i].group = gr;
            mas[i].max = sum / 4;
            mas[i].min = sum / 4;
            mas[i].student = 1;
            i++;
        }
    }
    int max = 0, gr;
    for(int j = 0; j < i; j++) {
        if(mas[j].max - mas[j].min > max && mas[j].student > 1) {
            gr = mas[j].group;
            max = mas[j].max - mas[j].min;
        }
    }
    printf("%d\n", gr);
    return 0;
}
