#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define Max 10000

typedef struct ListC {
    char val;
    struct List *next;
} ListC;

typedef struct StackC {
    char value;
    int size;
    ListC *front;
} StackC;

typedef struct Tree {
    char value;
    struct Tree *left;
    struct Tree *right;
} Tree;

typedef struct ListN {
    Tree *node;
    struct List *next;
} ListN;

typedef struct StackN {
    char value;
    int size;
    ListN *front;
} StackN;

Tree *Create(char value) {
    Tree* root_Tree = (Tree*) malloc(sizeof(Tree));
    root_Tree->value = value;
    root_Tree->left = root_Tree->right = NULL;
    return root_Tree;
}


int IsOperator(char a) {
    if(a == '+' || a == '-' || a == '*' || a == '/' || a == '^') return 1;
    return 0;
}

int IsDigit(char a) {
    if(a >= '0' && a <= '9') return 1;
    return 0;
}

int SizeM(char *mas) {
    int size = 0;
    while (*mas) {
        size++;
        mas++;
    }
    return size;
}

void PrintM(char *mas, int n) {
    printf("elem:\n");
    for (int i = 0; i < n; i++) {
        printf("%c", *mas);
        mas = mas + 1;
    }
    printf("\n");
}

void PushC(StackC * cur, char data) {
    ListC * tmp = (ListC*) malloc(sizeof(ListC));
    tmp->val = data;
    tmp->next = cur->front;
    cur->front = tmp;
    cur->size = cur->size + 1;
}

char PopC(StackC * cur) {
    ListC *out = cur->front;
    char buf;
    if (cur != NULL) {
        buf = out->val;
        cur->front = out->next;
        cur->size = cur->size - 1;
        free(out);

    }
    return buf;
}

char PeekC(StackC* stack) {
    if (stack->front == NULL) {
        return -1; 
    } else {

        return stack->front->val;
    }
}

int EmptyC(StackC* stack) {
    return stack->front == NULL;
}

int SizeC(StackC * cur) {
    return cur->size;
}

void PolishNote(char c, char *masElem, StackC *stk) {
    c = getchar();
    while (c != '\n') {
        if ((c >= '0') && (c <= '9')) {
            *masElem = c;
            masElem = masElem + 1;
        } else {
            if (c == '*' || c == '/' || c == '(' || c == '^') {
                PushC(stk, c);
            }
            if (c == '-' || c == '+') {
                if ((PeekC(stk) != '*') && (PeekC(stk) != '/') && (PeekC(stk) != '^')) {
                    PushC(stk, c);
                } else {
                    while (EmptyC(stk) == NULL) {
                        *masElem = PopC(stk);
                        masElem = masElem + 1;
                    }
                    PushC(stk, c);
                }
            }
            if (c == ')') {
                if (c != '(') {
                     *masElem = PopC(stk);
                    masElem = masElem + 1;
                }
                PopC(stk); 
            }
        }

        c = getchar();
    }
    while (EmptyC(stk) == NULL) {
        *masElem = PopC(stk);
        masElem = masElem + 1;
    }
}

void PushN(StackN * cur, Tree* data) {
    ListN * tmp = (ListN*) malloc(sizeof(ListN));
    tmp->node = data;
    tmp->next = cur->front;
    cur->front = tmp;
    cur->size = cur->size + 1;
}

Tree* PopN(StackN * cur) {
    ListN *out = cur->front;
    Tree* buf;
    if (cur != NULL) {
        buf = out->node;
        cur->front = out->next;
        cur->size = cur->size - 1;
        free(out);
    }
    return buf;
}

Tree* PeekN(StackN* stack) {
    return stack->front->node;
}

int EmptyN(StackN* stack) {
    return stack->front == NULL;
}

int SizeN(StackN * cur) {
    return cur->size;
}

Tree* BuildTree(int len, StackN *stk, char *mas) {
    if (len - 1 == 0) {
        return NULL;
    }
    for (int i = 0; i < len; ++i) {
        if (IsOperator(mas[i])) {
            Tree *x = PeekN(stk);
            PopN(stk);
            Tree *y = PeekN(stk);
            PopN(stk);
            Tree *node = Create(mas[i]);
            node->left = y;
            node->right = x;
            PushN(stk, node);

        } else {
            Tree *node = Create(mas[i]);
            node->value = mas[i];
            PushN(stk, node);
        }
    }
    return PeekN(stk);
}

void VisT(Tree *root, int count) {
    if (root != NULL) {
        for (int i = 0; i < count; ++i) {
            printf("|");
        }
    }
    printf("%c\n", root->value);
    if (root->left != NULL) {
        VisT(root->left, count + 1);
    }
    if (root->right != NULL) {
        VisT(root->right, count + 1);
    }
}

void PrintT(Tree *root) {
    VisT(root, 0);
}

int CharToInt(char a) {
    return a - '0';
}

void Task(Tree *tr) {
    char buf, var;
    if (tr == NULL) {
        return;
    }
    if (IsOperator(tr->value)) {
        if (tr->value == '^') {
            var = tr->left->value;
            buf = CharToInt(tr->right->value);
            tr->value = '*';
            for(int i = 0; i < buf - 2; i++) {
                tr->right->value = '*';
                tr->left->value = var;
                Tree *new1 = Create(var);
                tr->right->left = new1;
                Tree *new2 = Create('*');
                tr->right->right = new2;
                tr = tr->right;
            }
            tr->right->value = var;
        }
    }
    Task(tr->left);
    Task(tr->right);
}

int main(void) {
    char c, mas[Max];
    StackC * stk = (StackC*) malloc(sizeof(StackC));
    PolishNote(c, &mas[0], stk);
    printf("%d\n", SizeM(mas));
    PrintM(&mas[0], SizeM(mas));

    StackN * stkn = (StackN*) malloc(sizeof(StackN));
    BuildTree(SizeM(mas), stkn, mas);
    Tree* tree = PopN(stkn);
    PrintT(tree);

    Task(tree);
    putchar('\n');
    PrintT(tree);
    return 0;
}
