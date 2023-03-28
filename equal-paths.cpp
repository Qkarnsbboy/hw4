#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int depth(Node* root, int currHeight);


// Returns true if all paths from leaves to root are the same length (height),
//  *        and false otherwise
//  *
//  *        Note: this doesn't mean we are checking if the tree is full, but just that
//  *        any leaf node (wherever it may exist) has the same length path to the root 
//  *        as all others.

int depth(Node* root, int currHeight){
    int leftHeight = currHeight;
    int rightHeight = currHeight;

    
    //1. if leaf node
    if(root->left == NULL && root->right == NULL){
        return currHeight;
    }
    //2. left tree
    if(root->left != NULL){

        //recurse left
        leftHeight = depth(root->left, currHeight+1);
    }
    //3. right tree
    if(root->right != NULL){

        //recurse right
        rightHeight = depth(root->right, currHeight+1);
    }

    //return greatest height
    if(leftHeight > rightHeight){
        return leftHeight;
    }
    else {
        return rightHeight;
    }
    
}

bool equalPaths(Node * root)
{
    //empty
    if(root == NULL){
        return true;
    }
    //one node
    if(root->left == NULL && root->right == NULL){
        return true;
    }
    //one node left
    if(root->left != NULL && root->right == NULL){
        if(root->left->right != NULL && root->left->left != NULL){
            return (depth(root->left->left, 1) == depth(root->left->left, 1));
        }
        return true;
    }
    //one node right
    if(root->left == NULL && root->right != NULL){
        if(root->right->left != NULL && root->right->left != NULL){
            return (depth(root->right->left, 1) == depth(root->right->right, 1));
        }
        return true;
    }

    //recurse down
    return (depth(root->left, 1) == depth(root->right, 1));
}

