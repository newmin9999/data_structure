//
// Created by mihnhyuk on 24. 1. 23.
//
#include<stdio.h>
#include"rbt.h"

int     find_depth(node_t* node){
    if(node == NULL){
        return 0;
    }
    int left = find_depth(node->left_child);
    int right = find_depth(node->right_child);
    return (left > right ? left : right) + 1;
}

node_t* uncle(node_t* node){
    node_t* g = NULL;
    if (node->parent != NULL){
        g = node->parent->parent;
    }
    if(g != NULL){
        if(g->left_child == node->parent){
            return g->right_child;
        }else{
            return g->left_child;
        }
    }
    return NULL;
}

node_t *sibling(node_t* n){
    if (n == n->parent->left_child)
        return n->parent->right_child;
    else
        return n->parent->left_child;
}

void    print_recursive(node_t* n){
    if(n->color == BLACK){
        printf("%d", n->val);
    }else{
        printf(ANSI_COLOR_RED "%d" ANSI_COLOR_RESET, n->val);
    }
    printf("\n");

    if(n->left_child){
        print_recursive(n->left_child);
    }
    if(n->right_child){
        print_recursive(n->right_child);
    }
}

//int    is_leaf(node_t* node){
//
//}

void    replace_node(node_t* n, node_t* c){
    c->parent = n->parent;
    if(n->parent != NULL){
        if (n->parent->left_child == n) {
            n->parent->left_child = c;
        }
        else if (n->parent->right_child == n) {
            n->parent->right_child = c;
        }
    }
    if(n->val < c->val){
        c->left_child = n->left_child;
    }
    else{
        c->right_child = n->right_child;
    }
}

enum color tell_color(node_t* node){
    if(node == NULL){
        return BLACK;
    }
    return node->color;
}