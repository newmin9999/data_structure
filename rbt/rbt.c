//
// Created by mihnhyuk on 24. 1. 22.
//

#include <malloc.h>
#include "rbt.h"


node_t* create_node(int val){
    node_t*  root = (node_t*)malloc(sizeof(node_t));
    root->parent = NULL;
    root->left_child =  NULL;
    root->right_child =  NULL;
    root->val =  val;
    root->color =  RED;
    return root;
}

node_t* insert(node_t* root, int n){
    return insert_node(root, create_node(n));
}

node_t* insert_node(node_t* root, node_t* node){
    node_t* cur = root;
    //TODO: root, node validation
    // 위치 찾기
    while(1){
        if(cur->val > node->val){
            if(cur->left_child != NULL){
                cur = cur->left_child;
            }else{
                cur->left_child = node;
                node->parent = cur;
                break;
            }
        }else{
            if(cur->right_child != NULL){
                cur = cur->right_child;
            }else{
                cur->right_child = node;
                node->parent = cur;
                break;
            }
        }
    }

    if(node->parent->color == BLACK){
        return root;
    }else{
        node_t* u = uncle(node);
        if((u != NULL) && (u->color == RED)){
            recoloring(node);
        }else{
            reconstructing(node);
        }
    }
    while(root->parent){
        root = root->parent;
    }
    return root;
}

void recoloring(node_t* n){
    while(n->parent != NULL && (n->color == RED && n->parent->color == RED)){
        node_t* u = uncle(n);
        if(u != NULL && u->color == RED){
            n->parent->color = BLACK;
            u->color = BLACK;
            u->parent->color = RED;
            n = u->parent;
        }else{
            reconstructing(n);
            break;
        }
    }
    if(n->parent == NULL){
        n->color = BLACK;
    }
}

void reconstructing(node_t* n){
    if(n->parent == NULL){
        //이런 경우는 없다.
        return;
    }
    node_t* g = n->parent->parent;
    if(g == NULL){
        //이런 경우는 없다.
    }else if((n == n->parent->right_child) && (n->parent == g->left_child)){
        rotate_left(n->parent);
        rotate_grand(n->left_child);
    }else if(n == n->parent->left_child && n->parent == g->right_child){
        rotate_right(n->parent);
        rotate_grand(n->right_child);
    }else{
        rotate_grand(n);
    }
}

void rotate_left(node_t* n){
    node_t* right_child = n->right_child;
    node_t* parent = n->parent;

    if(right_child->left_child != NULL){
        right_child->left_child->parent = n;
    }
    n->right_child = right_child->left_child;
    n->parent = right_child;
    right_child->left_child = n;
    right_child->parent = parent;

    if(parent != NULL){
        if(parent->left_child == n){
            parent->left_child = right_child;
        }else{
            parent->right_child = right_child;
        }
    }
}

void rotate_right(node_t* n){
    node_t* left_child = n->left_child;
    node_t* parent = n->parent;

    if(left_child->right_child != NULL){
        left_child->right_child->parent = n;
    }
    n->left_child = left_child->right_child;
    n->parent = left_child;
    left_child->right_child = n;
    left_child->parent = parent;

    if(parent != NULL){
        // if문 없어도 될지도?
        if(parent->right_child == n) {
            parent->right_child = left_child;
        }else{
            parent->left_child = left_child;
        }
    }
}

void rotate_grand(node_t* n){
    node_t* g = NULL;
    if(n->parent != NULL && n->parent->parent != NULL){
        g = n->parent->parent;
    }
    n->parent->color = BLACK;
    g->color = RED;
    if(n == n->parent->left_child){
        rotate_right(g);
    }else{
        rotate_left(g);
    }
}


//TODO: 성공실패 리턴
node_t* delete(node_t* root, int n){
    node_t* cur = root;
    while(cur){
        if(cur->val == n){
            return delete_node(cur);
        }else if(cur->val > n){
            cur = cur->left_child;
        }else{
            cur = cur->right_child;
        }
    }
    return root;
}

node_t* delete_node(node_t* node){
    int left_depth = find_depth(node->left_child);
    int right_depth = find_depth(node->right_child);

    node_t* target;
    if(left_depth == 0 && right_depth == 0){
        target = node;
    }
    else if(left_depth > right_depth){
        target = node->left_child;
        while(target->right_child){
            target = target->right_child;
        }
    }else{
        target = node->right_child;
        while(target->left_child){
            target = target->left_child;
        }
    }
    node->val = target->val;
    return delete_node_with_0o1_child(target);
}

node_t* delete_node_with_0o1_child(node_t* node){
    if(node->color == RED){
        return delete_and_free(node);
    }else{
        node_t* s = sibling(node);
        node_t* p = node->parent;
        node_t* e = (node->left_child ? node->left_child : node->right_child);
        if(p == NULL){  //루트만 있는 트리
            return delete_and_free(node);
        }
        if(e != NULL && e->color == RED){
            e->color = BLACK;
            return delete_and_free(node);
        }
        // double black.
        if(tell_color(s) == RED){
            p->color = RED;
            s->color = BLACK;
            if(p->left_child == node){
                rotate_left(p);
            }else{
                rotate_right(p);
            }
        }
        else if(tell_color(s->left_child) == BLACK && tell_color(s->right_child)){ // case 1
            s->color = RED;
            if(p->color == RED){
                p->color = BLACK;
            }
        }else if(tell_color(s->left_child) == RED && tell_color(s->right_child) == BLACK){
            if(p->left_child == node){
                s->color = RED;
                s->left_child->color = BLACK;
                p->color = BLACK;
                rotate_left(p);
            }
            else{
                s->color = p->color;
                p->color = BLACK;
                s->left_child->color = BLACK;
                rotate_right(p);
            }
        }else if(tell_color(s->left_child) == BLACK && tell_color(s->right_child) == RED) {
            if (p->left_child == node) {
                s->color = p->color;
                p->color = BLACK;
                s->right_child->color = BLACK;
                rotate_left(p);
            } else {
                s->color = RED;
                s->right_child->color = BLACK;
                p->color = BLACK;
                rotate_right(p);
            }
        }else{ // 둘다 레드
            s->left_child->color = BLACK;
            s->right_child->color = BLACK;
        }
        return delete_and_free(node);
    }
}

// 리프노드 이거나, 자식이 하나만 있는 경우에만 사용.
node_t*    delete_and_free(node_t* node){

    if(!node->parent){
        //루트만 있는 트리인 경우.
        free(node);
        return NULL;
    }
    node_t* root = node->parent;
    if (node->parent->right_child == node) {
        node->parent->right_child = (node->left_child ? node->left_child : node->right_child);
    } else {
        node->parent->left_child = (node->left_child ? node->left_child : node->right_child);
    }
    free(node);
    while(root->parent){
        root = root->parent;
    }
    return root;
}