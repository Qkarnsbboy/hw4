#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here

    //1. rotateRight(AVLNode<Key,Value>* curr)
    void rotateRight(AVLNode<Key,Value>* node);

    //2. rotateLeft(AVLNode<Key,Value>* curr)
    void rotateLeft(AVLNode<Key,Value>* node);

    //3. insertFix(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node)
    void insertFix(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node);

    //4. removeFix(AVLNode<Key,Value>* node, int diff)
    void removeFix(AVLNode<Key,Value>* node, int diff);


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    // TODO

    //set temp to root node (have to cast)
    AVLNode<Key, Value>* temp = static_cast<AVLNode<Key, Value>*>(this->root_);

    //get key & get value
    Key insertKey = new_item.first;
    Value insertVal = new_item.second;

    //if root is null (manually insert)
    if(temp == NULL){
        AVLNode<Key, Value>* rootNode = new AVLNode<Key,Value>(insertKey, insertVal, NULL);

        //set balance to 0
        rootNode->setBalance(0);

        //set root
        this->root_ = rootNode;


        return;
    }

    //while temp is not null --> continue to traverse
    while(temp != NULL){
        //check if tempKey = insertKey
        if(insertKey == temp->getKey()){
            //overwrite current value
            temp->setValue(insertVal);
            return;
        }
        //if insertKey is less than
        else if (insertKey < temp->getKey()){
            //if left empty location
            if(temp->getLeft() == NULL){
                //insert
                AVLNode<Key, Value>* Left = new AVLNode<Key,Value>(insertKey, insertVal, temp);

                //update left
                temp->setLeft(Left);

                //set balance to 0
                Left->setBalance(0);

                //check and set balance of parent (only equal to 0 or 1 --> have a right child)
                if(temp->getBalance() == 1){
                    //set to 0 and done!
                    temp->setBalance(0);
                }
                //if balance of parent was 0
                else{

                    //update balance of parent to -1 (only left child)
                    temp->setBalance(-1);

                    //insertfix
                    insertFix(temp, Left);
                }

                return;
            }
            else{
                //otherwise traverse to left
                temp = temp->getLeft();
            }
            
        }
        //else if insertKey is greater than
        else{
            //if right location empty
            if(temp->getRight() == NULL){
                //insert
                AVLNode<Key, Value>* Right = new AVLNode<Key,Value>(insertKey, insertVal, temp);

                //update right
                temp->setRight(Right);

                //set balance to 0
                Right->setBalance(0);

                //check and set balance of parent (only or 0 or -1 --> have a left child)
                if(temp->getBalance() == -1){
                    //set to 0 and done
                    temp->setBalance(0);
                }
                //if balance is 0
                else{
                    //update balance of parent to 1 (only right child)
                    temp->setBalance(1);

                    //insert-fix
                    insertFix(temp,Right);
                }
                return;
            }
            //otherwise traverse to right
            else{
                temp = temp->getRight();
            }
        }
    }
}

//HELPER: insertFix
/*
    fixes the balance of the tree after inserting --> using rotateLeft and rotateRight
*/
template<class Key, class Value>
void AVLTree<Key,Value>::insertFix(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node){
    //1. base cases (if parent or grandparent is null)
    if( (parent == NULL) || (parent->getParent() == NULL) ){
        return;
    }

    //2. get grandparent
    AVLNode<Key,Value>* grand = parent->getParent();

    //3a if parent is left child of grand
    if(parent == grand->getLeft()){
        //3a1 update grandparents balance
        grand->updateBalance(-1);

        //Case 1: if grand balance is 0 --> return
        if(grand->getBalance() == 0){
            return;
        }
        //Case 2: if grand balance is -1 (don't know if balanced --> recurse)
        else if(grand->getBalance() == -1) {
            insertFix(grand, parent);
        }
        //Case 3: if grand balance is -2 --> must fix!
        else{
            //A. Zig-zig (if node is left child of parent)
            if(node == parent->getLeft()){
                //rotate right around grand
                rotateRight(grand);

                //update parent and grandparent balances to be 0
                parent->setBalance(0);
                grand->setBalance(0);

                //once fixed return
                return;
            }
            //B. Zig-zag (if node is right child of parent)
            else{
                //rotate left around parent
                rotateLeft(parent);
                //rotate right around grand
                rotateRight(grand);

                //Case 3a: balance of node was -1
                if(node->getBalance() == -1){
                    parent->setBalance(0);
                    grand->setBalance(1);
                    node->setBalance(0);
                }
                //Case 3b: balance of node was 0
                else if (node->getBalance() == 0) {
                    parent->setBalance(0);
                    grand->setBalance(0);
                    node->setBalance(0);
                }
                //Case 3c: balance of node was 1
                else{
                    parent->setBalance(-1);
                    grand->setBalance(0);
                    node->setBalance(0);
                }
                
                //once fixed return
                return;
            }
        }
    } //3b parent is right child of grand
    else{
        //3b1 update grandparents balance
        grand->updateBalance(1);

        //Case 1: if grand balance is 0 --> return
        if(grand->getBalance() == 0){
            return;
        }
        //Case 2: if grand balance is 1 (don't know if balanced --> recurse)
        else if(grand->getBalance() == 1) {
            insertFix(grand, parent);
        }
        //Case 3: if grand balance is 2 --> must fix!
        else{
            //A. Zig-zig (if node is right child of parent)
            if(node == parent->getRight()){
                //rotate left around grand
                rotateLeft(grand);

                //update parent and grandparent balances to be 0
                parent->setBalance(0);
                grand->setBalance(0);

                //once fixed return
                return;
            }
            //B. Zig-zag (if node is left child of parent)
            else{
                //rotate right around parent
                rotateRight(parent);
                //rotate left around grand
                rotateLeft(grand);

                //Case 3a: balance of node was 1
                if(node->getBalance() == 1){
                    parent->setBalance(0);
                    grand->setBalance(-1);
                    node->setBalance(0);
                }
                //Case 3b: balance of node was 0
                else if (node->getBalance() == 0) {
                    parent->setBalance(0);
                    grand->setBalance(0);
                    node->setBalance(0);
                }
                //Case 3c: balance of node was -1
                else{
                    parent->setBalance(1);
                    grand->setBalance(0);
                    node->setBalance(0);
                }
                
                //once fixed return
                return;
            }
        }
    }
    return;
}


/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO
     //1. find node (have to cast)
    AVLNode<Key,Value>* temp = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::internalFind(key));

    //could not find
    if(temp == NULL){
        return;
    }

    //if two children swap
    if(temp->getLeft() != NULL && temp->getRight() != NULL){
        //A. get predecessor
        AVLNode<Key,Value>* pred = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::predecessor(temp));

        //B. swap
        nodeSwap(temp, pred);
    }

    //declare diff and parent
    AVLNode<Key,Value>* parent = temp->getParent();
    int diff = 0;
    //initialize diff
    if(parent != NULL){
        //if node deleted is left child
        if(temp == parent->getLeft()){
            diff = 1;
        }
        else{
            diff = -1;
        }
    }

    //2. if leaf node (no children --> just remove)
    if(temp->getLeft() == NULL && temp->getRight() == NULL){
        
        //if temp is root
        if(temp == this->root_){
            this->root_ = NULL;
            delete temp;
        }
        else{
            //update parent
                //deleted is left child
            if(temp == temp->getParent()->getLeft()){
                temp->getParent()->setLeft(NULL);
            }
                //right child
            else{
                temp->getParent()->setRight(NULL);
            }

            //delete node
            delete temp;

            //patch tree
            removeFix(parent, diff);
        }
    }
    //3. if one child --> promote child
    else{
        //if temp is root
        if(temp == this->root_){
            //promote child
            if(temp->getLeft() != NULL){
                temp->getLeft()->setParent(NULL);
                this->root_ = temp->getLeft();
            }
            else{
                temp->getRight()->setParent(NULL);
                this->root_ = temp->getRight();
            }
            delete temp;
        }
        //left child of parent
        else if(temp == temp->getParent()->getLeft()){
            Node<Key, Value>* LChild = temp->getLeft();
            Node<Key, Value>* RChild = temp->getRight();
            Node<Key, Value>* Parent = temp->getParent();

            //leftchild of temp
            if(LChild != NULL){
                Parent->setLeft(LChild);

                //set LChild's parent to parent
                LChild->setParent(Parent);
            }
            //rightchild of temp
            else{
                Parent->setLeft(RChild);

                //set LChild's parent to parent
                RChild->setParent(Parent);
            }
            delete temp;

            //patch tree
            removeFix(parent, diff);
        }
        //right child of parent
        else{
            Node<Key, Value>* LChild = temp->getLeft();
            Node<Key, Value>* RChild = temp->getRight();
            Node<Key, Value>* Parent = temp->getParent();

            //leftchild of temp
            if(LChild != NULL){
                Parent->setRight(LChild);

                //set LChild's parent to parent
                LChild->setParent(Parent);
            }
            //rightchild of temp
            else{
                Parent->setRight(RChild);

                //set LChild's parent to parent
                RChild->setParent(Parent);
            }
            delete temp;

            //patch tree
            removeFix(parent, diff);
        }
    }
    
    return;
}
//HELPER: removeFix
/*
    patches tree by recursing up ancestor path and fixing any imbalances
    takes in current node, and int diff (to update balances based on what got deleted before)
*/
template<class Key, class Value>
void AVLTree<Key,Value>::removeFix(AVLNode<Key,Value>* node, int diff){
    //1. base case (node is null)
    if(node == NULL){
        return;
    }

    //2. compute next recursive calls arguments
    AVLNode<Key,Value>* parent = node->getParent();
    int nextDiff = 0;

        //if not NULL
        if(parent != NULL){
            //if n is left child (right heavy --> +1)
            if(node == parent->getLeft()){
                nextDiff = 1;
            }
            //right child (left heavy --> -1)
            else{
                nextDiff = -1;
            }   
        }
    
    //3a (if diff = -1) --> aka deleting right child
    if(diff == -1){
        //Case 1: balance of node + diff == -2 (out of balance)
        if( (node->getBalance() + diff) == -2){
            //get taller of children (left)
            AVLNode<Key,Value>* child = node->getLeft();

            //Case 1a: balance of child is -1 (zig-zig case)
            if(child->getBalance() == -1){
                //rotate right around node
                rotateRight(node);

                //balance of node & child is 0
                node->setBalance(0);
                child->setBalance(0);

                //continue to recurse
                removeFix(parent, nextDiff);
            }
            //Case 1b: balance of child is 0 (zig-zig case)
            else if(child->getBalance() == 0){
                //rotate right around node
                rotateRight(node);

                //balance of node is -1 (left-weighted)
                node->setBalance(-1);

                //balance of child is +1 (right-weighted)
                child->setBalance(1);

                //done recursing!
                return;
            }
            //Case 1c: balance of child is +1 (zig-zag case)
            else{
                //declare grandchild (right of child)
                AVLNode<Key,Value>* grandC = child->getRight();

                //rotateLeft around child
                rotateLeft(child);

                //rotateRight around node
                rotateRight(node);

                //1cA: balance of grandchild was 1
                if(grandC->getBalance() == 1){
                    node->setBalance(0);
                    child->setBalance(-1);
                    grandC->setBalance(0);
                }
                //1cB: balance of grandchild was 0
                else if (grandC->getBalance() == 0){
                    node->setBalance(0);
                    child->setBalance(0);
                    grandC->setBalance(0);
                }
                //1cC: balance of grandchild was -1
                else {
                    node->setBalance(1);
                    child->setBalance(0);
                    grandC->setBalance(0);
                }

                //continue recursing
                removeFix(parent, nextDiff);
            }
        }
        //Case 2: node + diff = -1 --> balance of node is -1
        else if( (node->getBalance() + diff) == -1){
            //set balance of node to -1
            node->setBalance(-1);

            //done recursing!
            return;
        }
        //Case 3: node + diff = 0 --> balanced but must keep recursing
        else {
            //set balance of node to 0
            node->setBalance(0);

            //keep recursing
            removeFix(parent, nextDiff);
        }
    }
    //3b (if diff = 1) --> aka deleting left child (MIRROR)
    else{
        //Case 1: balance of node + diff = 2 (out of balance)
        if( (node->getBalance() + diff) == 2){
            //get taller of children (right)
            AVLNode<Key,Value>* child = node->getRight();

            //Case 1a: balance of child is 1 (zig-zig case)
            if(child->getBalance() == 1){
                //rotate left around node
                rotateLeft(node);

                //balance of node & child is 0
                node->setBalance(0);
                child->setBalance(0);

                //continue to recurse
                removeFix(parent, nextDiff);
            }
            //Case 1b: balance of child is 0 (zig-zig case)
            else if(child->getBalance() == 0){
                //rotate left around node
                rotateLeft(node);

                //balance of node is 1 (right-weighted)
                node->setBalance(1);

                //balance of child is -1 (left-weighted)
                child->setBalance(-1);

                //done recursing!
                return;
            }
            //Case 1c: balance of child is -1 (zig-zag case)
            else{
                //declare grandchild (left of child)
                AVLNode<Key,Value>* grandC = child->getLeft();

                //rotateRight around child
                rotateRight(child);

                //rotateLeft around node
                rotateLeft(node);

                //1cA: balance of grandchild was -1
                if(grandC->getBalance() == -1){
                    node->setBalance(0);
                    child->setBalance(1);
                    grandC->setBalance(0);
                }
                //1cB: balance of grandchild was 0
                else if (grandC->getBalance() == 0){
                    node->setBalance(0);
                    child->setBalance(0);
                    grandC->setBalance(0);
                }
                //1cC: balance of grandchild was 1
                else {
                    node->setBalance(-1);
                    child->setBalance(0);
                    grandC->setBalance(0);
                }

                //continue recursing
                removeFix(parent, nextDiff);
            }
        }
        //Case 2: node + diff = 1 --> balance of node is 1
        else if( (node->getBalance() + diff) == 1){
            //set balance of node to -1
            node->setBalance(1);

            //done recursing!
            return;
        }
        //Case 3: node + diff = 0 --> balanced but must keep recursing
        else {
            //set balance of node to 0
            node->setBalance(0);

            //keep recursing
            removeFix(parent, nextDiff);
        }
    }
    return;
}

//HELPER: rotateRight
/*
    Taking left child --> making it parent --> making original parent the new right child
*/
template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* node){
    // Get the parent and left child of the given node
    AVLNode<Key,Value>* parent = node->getParent();
    AVLNode<Key,Value>* leftChild = node->getLeft();

    bool isLeftNode;

    // Check for the existence of the right child of the left child of the given node
    AVLNode<Key,Value>* rightChild = nullptr;
    if (leftChild->getRight() != nullptr) {
        // Store the right child and set the right child of the left child to null
        rightChild = leftChild->getRight();
        leftChild->setRight(nullptr);
    }

    // If the given node is the root, rotate the tree accordingly
    if (parent == nullptr) {

        this->root_ = leftChild;
        node->setParent(leftChild);
        leftChild->setRight(node);
        leftChild->setParent(nullptr);
    }

    // If the given node is not the root, rotate the tree accordingly
    else {

        // Determine if the given node is the left or right child of its parent
        if (parent->getLeft() == node) {
            isLeftNode = true;
        } else {
            isLeftNode = false;
        }

        // If the given node is the left child of its parent, set the left child of the parent to the left child of the given node
        // If the given node is the right child of its parent, set the right child of the parent to the left child of the given node
        if (isLeftNode) {
            parent->setLeft(leftChild);
        } else {
            parent->setRight(leftChild);
        }

        // Set the parent and right child of the left child of the given node to the appropriate nodes
        leftChild->setParent(parent);
        node->setParent(leftChild);
        leftChild->setRight(node);
    }

    // If the right child of the left child of the given node does not exist, set the left child of the given node to null
    // If the right child of the left child of the given node exists, set it as the left child of the given node
    if (rightChild == nullptr) {
        node->setLeft(nullptr);
    } else {
        node->setLeft(rightChild);
        rightChild->setParent(node);
    }


    
//----------------------------------------------
    // //check if y is right child and check if things are null
    
    // //if node is null or no left child
    // if(node == NULL || node->getLeft() == NULL ){
    //     return;
    // }

    // //if node is root (don't update parent)
    // if(node == this->root_){
    //     //just switch nodes
    //     AVLNode<Key, Value>* y = node;
    //     AVLNode<Key, Value>* x = node->getLeft();

    //     //2. if x had a right child, update it to be left of y now (and update it's parent)
    //     if(x->getRight() != NULL){
    //         AVLNode<Key, Value>* temp = node->getRight();
    //         y->setLeft(temp);
    //         temp->setParent(y);
    //     }

    //     //3. make y the new right child of x
    //     x->setRight(y);

    //     //4. update x to have new parent be null
    //     x->setParent(NULL);

    //     //5. update y's parent to x
    //     y->setParent(x);

    //     //6. update root
    //     this->root_ = x;
    // }
    // else{
    //     //local variables
    //     AVLNode<Key, Value>* parent = node->getParent();
    //     AVLNode<Key, Value>* y = node;
    //     AVLNode<Key, Value>* x = node->getLeft(); 

    //     //1. update parent to have x be the new child
    //     parent->setLeft(x);

    //     //2. if x had a right child, update it to be left of y now (and update it's parent)
    //     if(x->getRight() != NULL){
    //         AVLNode<Key, Value>* temp = node->getRight();
    //         y->setLeft(temp);
    //         temp->setParent(y);
    //     }

    //     //3. make y the new right child of x
    //     x->setRight(y);

    //     //4. update x to have a new parent
    //     x->setParent(parent);

    //     //5. update y's parent to x
    //     y->setParent(x);
    // }

    // return;
}

//HELPER rotateLeft
/*
    Taking right child --> making it parent --> making original parent the new left child
*/
template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* node){
    // Get the parent and right child of the given node
    AVLNode<Key,Value>* parent = node->getParent();
    AVLNode<Key,Value>* rightChild = node->getRight();

    bool isRightNode;

    // Check for the existence of the left child of the right child of the given node
    AVLNode<Key,Value>* leftChild = nullptr;
    if (rightChild->getLeft() != nullptr) {
        // Store the left child and set the left child of the right child to null
        leftChild = rightChild->getLeft();
        rightChild->setLeft(nullptr);
    }

    // If the given node is the root, rotate the tree accordingly
    if (parent == nullptr) {

        this->root_ = rightChild;
        node->setParent(rightChild);
        rightChild->setLeft(node);
        rightChild->setParent(nullptr);
    }

    // If the given node is not the root, rotate the tree accordingly
    else {

        // Determine if the given node is the left or right child of its parent
        if (parent->getRight() == node) {
            isRightNode = true;
        } else {
            isRightNode = false;
        }

        // If the given node is the left child of its parent, set the left child of the parent to the left child of the given node
        // If the given node is the right child of its parent, set the right child of the parent to the left child of the given node
        if (isRightNode) {
            parent->setRight(rightChild);
        } else {
            parent->setLeft(rightChild);
        }

        // Set the parent and left child of the right child of the given node to the appropriate nodes
        rightChild->setParent(parent);
        node->setParent(rightChild);
        rightChild->setLeft(node);
    }

    // If the left child of the right child of the given node does not exist, set the right child of the given node to null
    // If the left child of the right child of the given node exists, set it as the right child of the given node
    if (leftChild == nullptr) {
        node->setRight(nullptr);
    } else {
        node->setRight(leftChild);
        leftChild->setParent(node);
    }


 //--------------------------------------------------   
    // AVLNode<Key, Value>* parent = node->getParent();
    // AVLNode<Key, Value>* rightChild = node->getRight();
    // AVLNode<Key, Value>* leftGrandchild = rightChild->getLeft();

    // // Detach left grandchild from right child and attach it to node
    // node->setRight(leftGrandchild);
    // if (leftGrandchild != nullptr) {
    //     leftGrandchild->setParent(node);
    // }

    // // Attach right child to node's parent or make it root if node was root
    // if (parent == nullptr) {
    //     this->root_ = rightChild;
    //     rightChild->setParent(nullptr);
    // } else {
    //     rightChild->setParent(parent);
    //     if (node == parent->getLeft()) {
    //         parent->setLeft(rightChild);
    //     } else {
    //         parent->setRight(rightChild);
    //     }
    // }

    // // Attach node as left child of right child
    // rightChild->setLeft(node);
    // node->setParent(rightChild);
    
//--------------------------------------------------
    // //check if y is left child or things are null
    
    // //if node is null or no right child
    // if(node == NULL || node->getRight() == NULL ){
    //     return;
    // }

    // //if root
    // if(node == this->root_){
    //     AVLNode<Key, Value>* y = node;
    //     AVLNode<Key, Value>* x = node->getRight(); 

    //     //2. if x had a left child, update it to be right of y now (and update it's parent)
    //     if(x->getRight() != NULL){
    //         AVLNode<Key, Value>* temp = node->getLeft();
    //         y->setRight(temp);
    //         temp->setParent(y);
    //     }

    //     //3. make y the new left child of x
    //     x->setLeft(y);

    //     //4. update x to have a new parent be null (since its root)
    //     x->setParent(NULL);

    //     //5. update y's parent to x
    //     y->setParent(x);

    //     //6. update root
    //     this->root_ = x;
    // }
    // else{
    //     //local variables
    //     AVLNode<Key, Value>* parent = node->getParent();
    //     AVLNode<Key, Value>* y = node;
    //     AVLNode<Key, Value>* x = node->getRight(); 

    //     //1. update parent to have x be the new child
    //     parent->setRight(x);

    //     //2. if x had a left child, update it to be right of y now (and update it's parent)
    //     if(x->getRight() != NULL){
    //         AVLNode<Key, Value>* temp = node->getLeft();
    //         y->setRight(temp);
    //         temp->setParent(y);
    //     }

    //     //3. make y the new left child of x
    //     x->setLeft(y);

    //     //4. update x to have a new parent
    //     x->setParent(parent);

    //     //5. update y's parent to x
    //     y->setParent(x);
    // }

    // return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
