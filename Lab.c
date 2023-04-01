#include <stdio.h>
#include <stdlib.h>

#define Max_Size 1
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102
typedef int elem;

struct stack
{
    elem *data;
    int size;
    int top;
};


struct stack* createStack() {
    struct stack *out = NULL;
    out = malloc(sizeof(struct stack));
    if (out == NULL) {
        exit(OUT_OF_MEMORY);
    }
    out->size = Max_Size;
    out->data = malloc(out->size * sizeof(elem));
    if (out->data == NULL) {
        free(out);
        exit(OUT_OF_MEMORY);
    }
    out->top = 0;
    return out;
}

void resize(struct stack *stack) {
    stack->size += 1;
    stack->data = realloc(stack->data, stack->size * sizeof(elem));
    if (stack->data == NULL) {
        exit(STACK_OVERFLOW);
    }
}

void push(struct stack *stack, elem value) {
    if (stack->top >= stack->size) {
        resize(stack);
    }
    stack->data[stack->top] = value;
    stack->top++;
}

void init(struct stack * stk) {
    stk->top = 0;
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
        printf("%d\n", stk->data[i]);
    }
}

int pop(struct stack *stk) {
    int elem;
    if(stk->top > 0) {
        stk->top--;
        elem = stk->data[stk->top];
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