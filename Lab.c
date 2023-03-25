#include <stdio.h>
#include <stdlib.h>

#define Max_Size 100

struct stack
{
    int elem[Max_Size];
    int top;
};

void init(struct stack * stk) {
    stk->top = 0;
}

void push(struct stack * stk, int f) {
        stk->elem[stk->top] = f;
        stk->top++;
}

int getcount(struct stack *stk) {
    return stk->top;
}

int empty(struct stack *stk) {
    if(stk->top == 0) {
        return 1;
    }
    return 0;
}

void print(struct stack *stk) {
    int i;
    i = stk->top;
    if(empty(stk) == 1) {
        return;
    }
    while(i > 0) {
        i--;
        printf("%d\n", stk->elem[i]);
    }
}

int pop(struct stack *stk) {
    int elem;
    if(stk->top > 0) {
        stk->top--;
        elem = stk->elem[stk->top];
        return elem;
    }
}

void sort(int* s_arr, int first, int last)
{
    int i = first, j = last, x = s_arr[(first + last) / 2];
  
    do {
        while (s_arr[i] < x) i++;
        while (s_arr[j] > x) j--;
  
        if(i <= j) {
            if (s_arr[i] > s_arr[j]) {
                int s_arr1 = s_arr[i];
                s_arr[i] = s_arr[j];
                s_arr[j] = s_arr1;
            }
            i++;
            j--;
        }
    } while (i <= j);
  
    if (i < last)
        sort(s_arr, i, last);
    if (first < j)
        sort(s_arr, first, j);
}

int main() {
    struct stack * stk;
    int len1, len2;
    int elem;
    stk = (struct stack*)malloc(sizeof(struct stack));
    init(stk);
    printf("Введите число элементов стека первого\n");
    scanf("%d", &len1);
    printf("Введите элементы:");
    for(int i = 0; i < len1; i++) {
        scanf("%d", &elem);
        push(stk, elem);
    }
    printf("Введите число элементов стека второго\n");
    scanf("%d", &len2);
    printf("Введите элементы:");
    for(int i = 0; i < len2; i++) {
        scanf("%d", &elem);
        push(stk, elem);
    }
    print(stk);
    printf("\n");
    int mas[getcount(stk)], n = getcount(stk);
    for(int i = 0; i < len1 + len2; i++) {
        mas[i] = pop(stk);

    }
    sort(mas, 0, n - 1);
    printf("\n");
    for(int i = 0; i < len1 + len2; i++) {
        push(stk, mas[i]);
    }
    print(stk);
    return 0;
}
