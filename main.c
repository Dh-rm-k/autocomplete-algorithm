#include<stdio.h>
#include<stdint.h>
#include<assert.h>
#include "fruits.h"


typedef struct Node Node;
struct Node {
    Node* children[256];    
};


#define NODE_POOL_SIZE 1024
Node node_pool[NODE_POOL_SIZE] = {0};
int node_pool_size = 0;

Node* allocate_node(void) {
    assert(node_pool_size < NODE_POOL_SIZE);
    return &node_pool[node_pool_size++]; 
}

void insert_node(const char *text, Node* root) {
   if (text == NULL || *text == '\0') {
	   return;
   }
   if (root == NULL) 
	   return;

   int16_t index = *text;
   if (root->children[index] == NULL) {
   	root->children[index] = allocate_node();
   }
   insert_node(text+1,root->children[index]);
}

void init_tree(Node* root) {
    for(int i=0;i< sizeof(fruits)/sizeof(fruits[0]);i++){
	    insert_node(fruits[i],root);
    }
}


int main(void) {
    Node* stuff = allocate_node();
    init_tree(stuff);

    return 0;
}
