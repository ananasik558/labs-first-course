#include <stdio.h>
#include <stdlib.h>

struct tree{
    int key;
    struct tree*child;
    struct tree*sibling;
    struct tree*parent;
    struct tree*left;
    struct tree*right;
};
typedef struct tree node;

int getWidth(node* t, int level);
int height(node* t);

int check(node* t) {
    int h = height(t);
    int width, lastWidth;
    for(int i = 1; i <= h; i++) {
        width = getWidth(t, i);
        if(width > lastWidth) {
            return 0;
        }
        lastWidth = width;
    }
    return 1;
}

int getWidth(node* t, int level) {
    if(t == NULL) {
        return 0;
    }
    if(level == 1) {
        return 1;
    }
    if(level > 1) {
        return getWidth(t->left, level - 1) + getWidth(t->right, level - 1);
    }
}

int height(node* t) {
    if(t == NULL) {
        return 0;
    } else {
        int lHeight = height(t->left);
        int rHeight = height(t->right);
        return (lHeight > rHeight) ? (lHeight + 1) : (rHeight + 1);
    }
}

node *create(int parent) {
    node *tree = (node *) malloc(sizeof(node));
    tree->key = parent;
    tree->child = NULL;
    tree->sibling = NULL;
    tree->parent = NULL;
    return tree;
}

node *find_node(node* tree, int parent) {
    if (tree == NULL) {
        return NULL;
    }
    if (tree->key == parent) {
        return tree;
    }
    node* child = NULL;
    if (tree->child) {
        child = find_node(tree->child, parent);
        if (child != NULL) {
            return child;
        }
    }
    if (tree->sibling) {
        child = find_node(tree->sibling, parent);
        if (child != NULL) {
            return child;
        }
    }
}

void add(node* tree, int child, int parent) {
    node *res = find_node(tree, child);
    if (res == NULL) {
        return;
    }
    node *res_parent = res;
    if (res->child == NULL) {
        res->child = create(parent);
        res->child->parent = res;
        return;
    }
    res = res->child;
    while (res->sibling != NULL) {
        res = res->sibling;
    }
    res->sibling = create(parent);
    res->sibling->parent = res_parent;
}


void tree_show(node *child, int deep) {
    if (child != NULL) {
        for (int i = 0; i < deep; i++) {
            printf("    ");
        }
        printf("%d\n", child->key);
        if (child->child != NULL) {
            tree_show(child->child, deep + 1);
        }
        tree_show(child->sibling, deep);
    }
}

void tree_print(node *t) {
    tree_show(t, 0);
}


void tree_destroy(node *t) {
    if (t != NULL) {
        if (t->child != NULL) {
            tree_destroy(t->child);
        }
        if (t->sibling != NULL) {
            tree_destroy(t->sibling);
        }
    }
    free(t);
}

int main() {
    int root, count = 0;
    node *t = NULL;
    scanf("%d", &count);
    scanf("%d", &root);
    t = create(root);
    for(int i = 0; i < count - 1; ++i) {
        int parent, child;
        scanf("%d%d", &child, &parent);
        add(t, child, parent);
    }
    if (check(t)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    tree_print(t);
    tree_destroy(t);
    return 0;
}
