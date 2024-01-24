//
// Created by mihnhyuk on 24. 1. 23.
//

#ifndef _RBT_H
#define _RBT_H

#define ANSI_COLOR_RED     "\x1b[31m"
//#define ANSI_COLOR_GREEN   "\x1b[32m"
//#define ANSI_COLOR_YELLOW  "\x1b[33m"
//#define ANSI_COLOR_BLUE    "\x1b[34m"
//#define ANSI_COLOR_MAGENTA "\x1b[35m"
//#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


enum color{
    RED,
    BLACK
};

typedef struct node_s node_t;
struct node_s {
    node_t*     parent;
    node_t*     left_child;
    node_t*     right_child;
    int         val;
    enum color  color;
};

node_t*     create_node(int val);
node_t*     insert_node(node_t* root, node_t* node);
void        rotate_left(node_t* n);
void        rotate_right(node_t* n);
void        rotate_grand(node_t* n);
void        recoloring(node_t* n);
void        reconstructing(node_t* n);
node_t*     insert(node_t* root, int n);

node_t*     delete_node_with_0o1_child(node_t* node);
node_t*     delete_and_free(node_t* node);
node_t*     delete_node(node_t* node);
node_t*     delete(node_t* root, int n);

int         find_depth(node_t* node);
void        print_recursive(node_t* n);
node_t*     sibling(node_t* n);
node_t*     uncle(node_t* node);
enum color  tell_color(node_t* node);

void    rbt_test_script();
#endif //_RBT_H
