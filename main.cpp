#include <iostream>
#include<fstream>


/*
 *This program reads data from a file and inserts every alphabetical character 
 *into a binary search tree, and tracks the number of occurrences of each letter. 
 *
 *Data Structures @ TCC
 *
 *Arick Mounts
 *
 */

using namespace std;
struct node{
  char value;
  int amount = 1;
  node * left;
  node * right;
};

struct node * insert( struct node * root, char c );
void printTree(struct node* root);
void printTreeReverse(struct node * root);
int addTotalLetters(struct node * root);
char lowestVal(struct node * root);
char highestVal(struct node * root);

struct node * free_tree(struct node * root);

int main() {

  ifstream fileIn ("input.txt");
  char c;
  struct node * root = NULL;
  

  while(fileIn.get(c)){
    if (isalpha(c)){
      root = insert (root, tolower(c));
    }
  }

 cout << "In order:" << endl;
  printTree(root);
  cout << "Reverse order: " << endl;
  printTreeReverse(root);
  cout << "Total number of letters: " << addTotalLetters(root) << endl;
  cout << "Lowest Value: " << lowestVal(root) << endl;
  cout << "Highest Value: " << highestVal(root) << endl;

  root = free_tree(root);
  fileIn.close();
}

struct node * insert( struct node * root, char c ){
	
	if( !root ){
		struct node * new_node =  (struct node * ) new struct node;
		new_node->value = c;
		new_node->left = NULL;
		new_node->right = NULL;
		return new_node;
	}else{
    if(c == root->value){
      root->amount ++;
    }
		else if( c <= root->value ){
			root->left = insert( root->left, c );
		}else{
			root->right = insert( root->right, c );
		}
		return root;
	}
}

struct node * free_tree(struct node * root){
  if(root != NULL) {
        root->right = free_tree(root->right);
        root->left = free_tree(root->left);
        delete(root);
    }
	return NULL;
}

void printTree(struct node *root){
    if(!root){
      return;
    }
    printTree(root->left);
    cout << root->value << ", " << root->amount << endl;
    printTree(root->right);
}

char lowestVal(struct node * root){
  while (root->left != NULL ){
    root = root->left;
  }
  return root->value;
}


char highestVal(struct node * root){
   while (root->right != NULL ){
    root = root->right;
  }
  return root->value;
}

void printTreeReverse(struct node * root){
  if(!root){
    return;
  }
  printTree(root->right);
  cout << root->value << ", " << root->amount << endl;
  printTree(root->left);
}

int addTotalLetters(struct node * root){
  if(!root){
    return 0;
  }
  return addTotalLetters( root->right ) + addTotalLetters( root->left ) + root->amount;
}