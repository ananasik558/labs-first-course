#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char n;
    char *student;
    char sex[1];
    char group[3];
    char s1[1];
    char s2[1];
    char s3[1];
    char s4[1];
} File;

int main() {
    FILE* fp = fopen("data.csv", "r");
    FILE* out = fopen("data.bin", "a");
    int n = 100;
    char buf[n];
    int column = 0;
    int row = 0;
    while (fgets(buf,n, fp)) {
        column = 0;
        row ++;
        if(row == 1) continue;
        File* f = (File*) malloc (sizeof(File));
        int index = 0;
        char student[100];
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (buf[i] == '\n') {
                    break;
            }
            if (buf[i] == ';') {
                ++column;
                index = 0;
                continue;
            }
            if (column == 0) {
                ++count;
                student[count - 1] = buf[i];
            }
            if (column == 1) { 
                f -> n = count;
                f -> student = student;
                f -> sex[index] = buf[i];
            }
            if (column == 2) {
                f -> group[index] = buf[i];
            }
            if (column == 3) {
                f -> s1[index] = buf[i];
            }
            if (column == 4) {
                f -> s2[index] = buf[i];
            }
            if (column == 5) {
                f -> s3[index] = buf[i];
            }
            if (column == 6) {
                f -> s4[index] = buf[i];
                break;
            }
            ++index;
        }
        fwrite(f, sizeof(File), 1, out);
    }
    fclose(fp);
    fclose(out);
    return 0;
}
