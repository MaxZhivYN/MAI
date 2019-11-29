#include "tree.h"
#include "transform.h"
#include <math.h>

 long int pow1(long int x, unsigned int n)
 {
    if (n==0)
        return 1;
    else if (n==1)
        return x;
    else if (n % 2 == 0 )
        return pow1( x * x, n/2);
    else
        return pow1( x * x, n /2)*x;
 }

int match_power(Tree *t)
{
    return ((*t) != NULL) && ((*t)->node.type == OPERATOR)
           && ((*t)->node.data.operator_name == '^')
           && (((*t)->left->node.type == INTEGER) ||
               ((*t)->left->node.type == FLOATING))
           && ((*t)->right->node.type == INTEGER);
}

void transform_power(Tree *t)
{
    Tree tmp = (Tree) malloc(sizeof(struct tree_node));
    tmp->node.type = (*t)->left->node.type;

    float right = (*t)->right->node.data.value_int;

    if (tmp->node.type == INTEGER)
        tmp->node.data.value_int = pow1((*t)->left->node.data.value_int, right);
    else // if (tmp->node.type == FLOATING)
        tmp->node.data.value_float = pow1((*t)->left->node.data.value_float, right);

    tmp->left  = NULL;
    tmp->right = NULL;

    tree_delete(t);
    *t = tmp;
}

void tree_transform(Tree *t)
{
    if ((*t) != NULL) {
        tree_transform(&((*t)->left));
        tree_transform(&((*t)->right));

        if (match_power(t)) {
            transform_power(t);
        }
    }
}
