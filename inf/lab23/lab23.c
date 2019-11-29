#include <stdio.h>
#include <stdlib.h>

typedef int Type;

typedef struct TagTree {
    Type value;
    struct TagTree *son;
    struct TagTree *bro;
} Tree;


Tree* tree_find_parent(Tree *tree, Type father) {
    if (tree == NULL) {
        return NULL;
    }
    if (tree->value == father) {
        return tree;
    }
    Tree *parent_node = tree_find_parent(tree->son, father);
    if (parent_node == NULL) {
        parent_node = tree_find_parent(tree->bro, father);
    }
    return parent_node;
}

Tree* tree_find_parent1(Tree *tree, Tree *base)
{
    Tree *add = NULL;
    if (tree->son == base)
    {
        return tree;
    }
    if (tree->bro == base)
    {
        return tree;
    }
    if (tree->son != NULL && add == NULL)
    {
        add = tree_find_parent1(tree->son, base);
        return add;
    }
    if (tree->bro != NULL && add == NULL)
    {
        add = tree_find_parent1(tree->bro, base);
        return add;
    }
    if (tree == base)
    {
        return tree;
    }
    
}

int *T;

int create_node(Tree **tree, Type value) {
    *tree = malloc(sizeof(Tree));
    if (*tree == NULL) {
        return 1;
    }
    (*tree)->value = value;
    (*tree)->son = NULL;
    (*tree)->bro = NULL;
    //T = &(*tree);
    return 0;
}

int tree_add(Tree **tree, Type father, Type son) {
    if (*tree == NULL) {
        return create_node(tree, son);
    }

    Tree *parent_node = tree_find_parent(*tree, father);
    if (parent_node == NULL) {
        return 2;
    }

    if (parent_node->son == NULL) {
        return create_node(&(parent_node->son), son);   
    } else {
        Tree *youngest_brother = parent_node->son;
        while (youngest_brother->bro != NULL) {
            youngest_brother = youngest_brother->bro;
        }
        return create_node(&(youngest_brother->bro), son);
    }

    return 0;
}

void split(Tree **tree) {
    Tree *tmp = (*tree)->bro;
    (*tree)->son = tmp->son;
    (*tree)->value = tmp->value;
    (*tree)->bro = tmp->bro;
    free(tmp);
    tmp = NULL;
}


Tree* destroy_Tree(Tree **base) {
    if ((*base) == NULL)
    {
        return NULL;
    }
    
    if ((*base)->son != NULL)
    {
    destroy_Tree(&((*base)->son));
    }
    
    if ((*base)->bro != NULL)
    {
    destroy_Tree(&((*base)->bro));
    }
    
    if ((*base)->son == NULL && (*base)->bro == NULL)
    {
        free(*base);
        *base = NULL;       
    }
}

int sum_maxstep = 0;

void maxstep(Tree *base, int *p) {
    
    if (base->bro != NULL) {
        sum_maxstep++;
        //printf("1 ");
        maxstep(base->bro, p);
    }

    if (*p < sum_maxstep) {
        *p = sum_maxstep;
        //printf("2 ");
    }
    
    if (base->son != NULL) {
        sum_maxstep = 0;
        //printf("3 ");
        maxstep(base->son, p);
    }

    if (base == NULL) {
        return;
    }
    
    
    
}


void print_node(Type value, int level) {
    for (int i = 0; i < level; ++i) {
        printf("--");
    }
    printf("%d\n", value);
}

void tree_lvl_print(Tree *tree, int level) {
    if (tree == NULL) {
        return;
    }
    print_node(tree->value, level);
    tree_lvl_print(tree->son, level + 1);
    tree_lvl_print(tree->bro, level);
}

void tree_print(Tree *tree) {
    tree_lvl_print(tree, 0);
}

int main() {
    Tree *tree = NULL;
    Type father = 1, son = 1;
    int cmd, err, a;
    int *p = &a;

    while (scanf("%d", &cmd) == 1) {
        if (cmd == 2){
            if (scanf("%d", &father) == 1) {
                Tree *base = tree_find_parent(tree, father);
                destroy_Tree(&(base->son));
                if (base->bro != NULL)
                {
                    split(&base);
                }
                else if (base->bro == NULL)
                {
                    Tree *del = tree_find_parent1(tree, base);
                    if (del->son == base)
                    {
                        free(base);
                        del->son = NULL;
                        tree_print(tree);
                        continue;
                    }
                    if (del->bro == base)
                    {
                        free(base);
                        del->bro = NULL;
                        tree_print(tree);
                        continue;
                    }
                    if (del == base)
                    {
                        free(tree);
                        tree = NULL;
                        tree_print(tree);
                        continue;
                    }
                }
                tree_print(tree);

            }    
        }
        if (cmd == 1){
            if (scanf("%d%d", &father, &son) == 2) {
                err = tree_add(&tree, father, son);
                if (err == 0) {
                    tree_print(tree);
                } else if (err == 1) {
                    printf("No memory\n");
                } else {
                    printf("Wrong father value");
                }
            } else {
                printf("Not 2 arguments for add\n");
            }            
        }
        if (cmd == 3) {
            break; 
        }
        if (cmd == 4) {
            maxstep(tree, p);
            printf("%d\n", (*p + 1));
        }
    } 

    destroy_Tree(&tree);

    return 0;
}