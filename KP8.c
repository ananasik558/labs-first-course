#include <stdio.h>

void PrintTable(int mas[][2], int n) {
    for(int i = 0; i < n; i++) {
        printf("%d %d\n", mas[i][0], mas[i][1]);
    }
}

void QuickSort(int mas[][2], int first, int last) {
    int key, value;
    int i = first;
    int j = last;
    key = mas[first][0];
    value = mas[first][1];
    while (first < last) {
        while ((mas[last][0] >= key) && (first < last)) {
            --last;
        }
        if (first != last) {
            mas[first][0] = mas[last][0];
            mas[first][1] = mas[last][1];
            ++first;
        }
        while ((mas[first][0] <= key) && (first < last)) {
            ++first;
        }
        if (first != last) {
            mas[last][0] = mas[first][0];
            mas[last][1] = mas[first][1];
            --last;
        }
    }
    mas[first][0] = key;
    mas[first][1] = value;
    key = first;
    if (i < key) {
        QuickSort(mas, i, key - 1);
    }
    if (j > key) {
        QuickSort(mas, key + 1, j);
    }
}

void BinSearch(int mas[][2], int n, int key) {
    int first = 0;
    int last = n - 1;
    while(first <= last) {
        int mid = (first + last) / 2;
        if(mas[mid][0] == key) {
            printf("Значение %d\n", mas[mid][1]);
            return;
        }
        if(mas[mid][0] > key) {
            last = mid;
        }
        if(mas[mid][0] < key) {
            first = mid;
        }
    }
}

int main() {
    printf("Введите количество элементов\n");
    int n;
    scanf("%d", &n);
    int mas[n][2];
    printf("Введите ключ и элемент через пробел\n");
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &mas[i][0], &mas[i][1]);
    }
    printf("\n");
    PrintTable(mas, n);
    QuickSort(mas, 0, n - 1);
    printf("\n");
    PrintTable(mas, n);
    printf("\n");
    int flag = 1;
    while(flag) {
        int key, var;
        printf("1. Найти ключ  2. Выход\n");
        scanf("%d", &var);
        if(var == 1) {
            printf("Введите ключ\n");
            scanf("%d", &key);
            BinSearch(mas, n, key);
        }
        if(var == 2) {
            flag = 0;
        }
    }
    return 0;
}