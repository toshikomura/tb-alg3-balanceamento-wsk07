//In this library you find all the functions used in the program 

//This structure declares a tree avl
typedef struct avl{
        int    balancing;
        int    key;
        struct avl *right;
        struct avl *left;
} tree;

tree *create_tree();

tree *create_node( int );

int search( tree *, int );

tree *rotate_right( tree * );

tree *rotate_left( tree * );

tree *rotate_RL( tree * );

tree *rotate_LR( tree * );

int insert( tree **, int );

tree *remove_left( tree ** );

tree *remove_right( tree ** );

int remove_bs( tree * );

int remove_( tree **, int );

void print_( tree * );
