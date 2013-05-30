#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

//This function just creates a NULL tree
tree *create_tree(){
        return NULL;
}

//It creates a new node with the n element 
tree *create_node( int n ){
        tree *new = malloc(sizeof(tree));

        new->key = n;
        new->balancing = 0;
        new->right = NULL;
        new->left = NULL;

        return new;
}

//In this function you can search a n element
//and the function will print the route until n
int search( tree *t, int n ){
        tree  *aux;
        aux = t;

        while ( aux!=NULL && aux->key!=n ){
                if ( aux->key > n ){
                        fprintf(stdout, "%d", aux->key);
                        aux = aux->left;
                        if ( aux!=NULL ){
                                fprintf(stdout, ",");
                        }

                }    
                else{
                        fprintf(stdout, "%d", aux->key);
                        aux = aux->right;
                        if ( aux!=NULL ){
                                fprintf(stdout, ",");
                        }
                }
        }

        if ( aux!=NULL ){
                fprintf(stdout, "%d\n", aux->key);
                return 1;
        }
        
        fprintf(stdout, "\n");
        
        return 0;
}

//This function rote the tree on right
tree *rotate_right( tree *t ){
        tree *aux;

        aux = t->left;
        t->left = aux->right;
        aux->right = t;

        //The prove that expression is in README
        t->balancing += -1 - (aux->balancing > 0) * aux->balancing;
        aux->balancing += -1 + (t->balancing <= 0) * t->balancing;

        return aux;
}

//This function rote the tree on left
tree *rotate_left( tree *t ){
        tree *aux;

        aux = t->right;
        t->right = aux->left;
        aux->left = t;

        //The prove that expression is in README
        t->balancing += 1 - (aux->balancing < 0) * aux->balancing;
        aux->balancing += 1 + (t->balancing >= 0) * t->balancing;

        return aux;
}

//This function rote the tree on right and left using the functions that
//simple rote
tree *rotate_RL( tree *t ){
        tree *t_right, *new_node;

        t_right = t->right;
        t->right = rotate_right(t_right);
        new_node = rotate_left(t);

        return new_node;
}

//This function rote the tree on left and right using the functions that
//simple rote
tree *rotate_LR( tree *t ){
        tree *t_left, *new_node;

        t_left = t->left;
        t->left = rotate_left(t_left);
        new_node = rotate_right(t);

        return new_node;
}

//This function insert a new node n 
//if it there is the function doesn't insert the element
int insert( tree **t, int n ){
        if ( (*t) == NULL ){
                (*t) = create_node(n);
                return 1;
        }

        if ( (*t)->key == n )
                return 0;


        int aux=0; 

        if ( (*t)->key > n ){
                if ( aux = insert(&(*t)->left, n )){
                        if ( (*t)->right == NULL){
                                (*t)->balancing += aux;
                                if ( (*t)->balancing == 2){
                                        if ( (*t)->left->balancing == 1 ){
                                                (*t)=rotate_right(*t);
                                                return 0;
                                        }
                                        else{
                                                if ( (*t)->left->balancing == -1){
                                                        (*t)=rotate_LR(*t);
                                                        return 0;
                                                }
                                        }
                                }
                                else
                                        return 1;
                        }
                        else{
                                (*t)->balancing += aux;
                                if ( (*t)->balancing == 0 ){
                                        return 0;
                                }
                                return 1;
                        }
                }
                else{
                        return 0;
                }
        }
        else{
                if ( aux = insert( &(*t)->right, n ) ){
                        if ( (*t)->left == NULL ){
                                (*t)->balancing -= aux;
                                if ( (*t)->balancing == -2){
                                        if ( (*t)->right->balancing == -1){
                                                (*t)=rotate_left(*t);
                                                return 0;
                                        }
                                        else{
                                                /* andre bobao ! */
                                                if ( (*t)->right->balancing == 1){
                                                        (*t)=rotate_RL(*t);
                                                        return 0;
                                                }
                                        }
                                }
                                else
                                        return 1;
                        }
                        else{
                                (*t)->balancing -= aux;
                                if ( (*t)->balancing == 0){
                                        return 0;
                                }
                                return 1;
                        }
                }
                else{
                        return 0; 
                }
        }
}

//This function replaces the key of the node for the right kid
//and remove it
tree *remove_left( tree **t ){
   tree *aux;
        
   aux = (*t);
   (*t) = aux->right;
   free(aux);

   return (*t);
}

//This function replaces the key of the node for the left kid
//and remove it
tree *remove_right( tree **t ){
   tree *aux;

   aux = (*t);
   (*t) = aux->left;
   free(aux);

   return (*t);
}

//This function returns the biggest of smallest element of the tree
int remove_bs( tree *t ){
  tree *aux,*aux2;

  aux = t;
  aux = aux->left;

  while ( aux->right != NULL )
      aux = aux->right;
  
  return aux->key;
}

//This function removes the n element
int remove_( tree **t, int n ){
   int key, sub;

   if ( (*t) == NULL )
      return 0;
   
   if ( (*t)->key == n ){
      if ( (*t)->left == NULL ){
         (*t) = remove_left(t);
         return 1;
      }
      if ( (*t)->right == NULL ){
         (*t) = remove_right(t);
         return 1;
      }
      (*t)->key = remove_bs(*t);
      if ( remove_(&(*t)->left,(*t)->key) )
         return 1;
   }

   if ( (*t)->key > n ){
      if ( remove_(&((*t)->left),n) ){
         if ( (*t)->right == NULL ){
            (*t)->balancing -= 1;
            return 1;
         }
         else{
            key = (*t)->balancing;
            (*t)->balancing -= 1;
            if ( (*t)->balancing == -2 ){
               if ( (*t)->right->balancing <= 0 ){
                  (*t) = rotate_left(*t);
                  //The explanation of this is in the README
                  if ( sub = key-(*t)->balancing == 0 || sub == -2 || sub == 2 )
                     return 0; 
                  else
                     return 1;
               }
               else{
                  (*t) = rotate_RL(*t);
                  return 1;
               }
            }
            else
               return 0;
            
            return 1;
         }
      }
      else
         return 0;
   
   }
   else{
      if ( remove_(&((*t)->right),n) ){
         if ( (*t)->left == NULL ){
            (*t)->balancing += 1;
            return 1;
         }
         else{
            key = (*t)->balancing;
            (*t)->balancing += 1;
            if ( (*t)->balancing == 2 ){
                    if ( (*t)->left->balancing >= 0 ){
                        (*t) = rotate_right(*t);
                        //The explanation of this is in the README
                        if ( sub = key-(*t)->balancing == 0 || sub == -2 || sub == 0 )
                           return 0;
                        else
                           return 1;
                        
                    }
                     else{
                        (*t) = rotate_LR(*t);
                        return 1;
                     }
            }
            else
               return 0;
            
            return 1;
         }
      }
      else
         return 0;
      
   }
}

//This function just prints the tree in stdout
void print_( tree *t ){
        if ( t==NULL ){
                fprintf(stdout, "()");
                return;
        }
        fprintf(stdout,)
        fprintf(stdout, "(");

        fprintf(stdout, "%d,", t->key);

        print_(t->left);
        fprintf(stdout, ",");
        print_(t->right);
        
        fprintf(stdout, ")");
}
