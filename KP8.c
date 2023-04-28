#include <stdio.h>
#include <stdlib.h>

typedef enum {
    RED,
    BLUE,
    YELLOW,
    BLACK,
    WHITE
} en;

typedef struct list{
    en key;
    struct list *next;
    struct list *prev;
    struct list *head;
} list;

list *init (en value) {
    list * lst = (list* )malloc(sizeof(list));
    lst->key = value;
    lst->next = NULL;
    lst->prev = NULL;
    lst->head = lst;
    return lst;
}

list *Add(list *lst, en value, int place) {
    int count = 0;
    while(count != place) {
        if(lst->next != NULL) {
            lst = lst->next;
            count++;
        } else {
            break;
        }
    }
    list *tmp, *link;
    tmp = (list *)malloc(sizeof(list *));
    link = lst->next;
    lst->next = tmp;
    tmp->key = value;
    tmp->next = link;
    tmp->prev = lst;
    if(link != NULL) {
        link->prev = tmp;
        return tmp;
    }
}

int size(list *lst) {
    int count = 0;
    while(lst != NULL) {
        count++;
        lst = lst->next;
    }
    return count;
}

void *delete(list *lst, int place) {
    if(place <= size(lst)) {
        int number = 1;
        while(number != place) {
            if(lst != NULL) {
                lst = lst->next;
                number++;
            } else {
                break;
            }
        }
    }
    list *linkNext, *lintPrev;
    linkNext = lst->next;
    lintPrev = lst->prev;
    if (lst->prev != NULL) lst->prev->next = linkNext;
    if (lst->next != NULL) lst->next->prev = lintPrev;
    free(lst);
    return lst;
}

void *print(list *lst) {

    while(lst->prev != NULL) {
        lst = lst->prev;
    }
    while(lst != NULL) {
        switch (lst->key) {
            case BLUE:
            printf("blue ");
            break;

            case YELLOW:
            printf("yellow ");
            break;

            case BLACK:
            printf("black ");
            break;

            case WHITE:
            printf("white ");
            break;
            
            case RED:
            printf("red ");
            break;
        }
        lst = lst->next;
    }
    printf("\n");
    return lst;
}

list *task(list *lst, int k) {
    if(k > size(lst)) {
        printf("You are wrong");
    } else {
        en elem;
        while(lst->next != NULL) {
            lst = lst->next;
        }
        elem = lst->key;
        while(lst->prev != NULL) {
            lst = lst->prev;
        }
        for(int i = 0; i < k; i++) {
            list *tmp;
            tmp = (list *)malloc(sizeof(list *));
            tmp->next = lst;
            tmp->prev = NULL;
            tmp->key = elem;
            lst->prev = tmp;
            lst = lst->prev;
        }
    }
    return lst;
}

int main() {
    int k;
    list *lst = init(RED);
    Add(lst, BLUE, 1);
    Add(lst, BLACK, 2);
    Add(lst, YELLOW, 3);
    Add(lst, WHITE, 3);
    print(lst);
    delete(lst, 2);
    print(lst);
    printf("Write k\n");
    scanf("%d", &k);
    task(lst, 2);
    print(lst);
    return 0;
}
