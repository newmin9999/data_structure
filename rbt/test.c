//
// Created by mihnhyuk on 24. 1. 23.
//
#include<stdio.h>
#include"rbt.h"

void    rbt_test_script(){
    node_t* root = create_node(1);
    root->color = BLACK;
    for(int i = 2 ; i <= 7 ; i++){
        root = insert(root, i);
    }
    for(int i = 1 ; i <= 7 ; i++){
        root = delete(root, i);
    }
    print_recursive(root);
}