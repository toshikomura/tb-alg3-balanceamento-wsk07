//This program is the main of the library avl-tree
//Use q to exit of the execution of the program
//Use i to insert a new element
//Use r to remover a element
//And use b to search a element
#include <stdio.h>
#include "avl-tree.h"

int main(){
    char option;
    int  n;
    tree *t;

    t = create_tree();

    while (1){
        fscanf(stdin, "%c", &option);
            switch (option){
                case 'q': return 0;
                case 'i': fscanf(stdin, "%d", &n);
                          insert(&t, n);
                          print_(t);
                          fprintf(stdout, "\n");
                          break;
                case 'r': fscanf(stdin, "%d", &n);
                          remove_(&t, n);
                          print_(t); 
                          fprintf(stdout, "\n");
                          break;
                case 'b': fscanf(stdin, "%d", &n);
                          search(t,n);
                          break;
            }
    }

    return 0;
}
