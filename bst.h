#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here

    //for isBalanced()
    int depth(Node<Key,Value>* root, int currHeight) const;
    bool nodeBalanced(Node<Key, Value>* root) const;

    //for iterator
    static Node<Key, Value>* successor(Node<Key, Value>* current);

    //for clear
    void trickleDownDelete(Node<Key,Value>* next);


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    //set current to ptr given
    current_ = ptr;
    
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    //check values of current
    return(current_ == rhs.current_);
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return(current_ != rhs.current_);
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    //later --> reverse predecessor
    current_ = successor(current_);
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    this->clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    //set temp to root node
    Node<Key, Value>* temp = root_;

    //get key & get value
    Key insertKey = keyValuePair.first;
    Value insertVal = keyValuePair.second;

    //if root is null (manually insert)
    if(temp == NULL){
        Node<Key, Value>* rootNode = new Node<Key,Value>(insertKey, insertVal, NULL);

        //set root
        root_ = rootNode;
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
                Node<Key, Value>* Left = new Node<Key,Value>(insertKey, insertVal, temp);

                //update left
                temp->setLeft(Left);

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
                Node<Key, Value>* Right = new Node<Key,Value>(insertKey, insertVal, temp);

                //update right
                temp->setRight(Right);

                return;
            }
            //otherwise traverse to right
            else{
                temp = temp->getRight();
            }
        }
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO

    //1. find node
    Node<Key,Value>* temp = internalFind(key);

        //could not find
    if(temp == NULL){
        return;
    }

    //if two children swap
    if(temp->getLeft() != NULL && temp->getRight() != NULL){
        //A. get predecessor
        Node<Key,Value>* pred = predecessor(temp);

        //B. swap
        nodeSwap(temp, pred);
    }

    //2. if leaf node (no children --> just remove)
    if(temp->getLeft() == NULL && temp->getRight() == NULL){
        
        //if temp is root
        if(temp == root_){
            root_ = NULL;
            delete temp;
            
        }
        else{
            //update parent
                //left
            if(temp == temp->getParent()->getLeft()){
                temp->getParent()->setLeft(NULL);
            }
                //right
            else{
                temp->getParent()->setRight(NULL);
            }

            //delete node
            delete temp;
        }
    }
    //3. if one child --> promote child
    else{
        //if temp is root
        if(temp == root_){
            //promote child
            if(temp->getLeft() != NULL){
                temp->getLeft()->setParent(NULL);
                root_ = temp->getLeft();
            }
            else{
                temp->getRight()->setParent(NULL);
                root_ = temp->getRight();
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
        }
    }
    return;
    // //check if left or right child
    // //left child
    // if(temp->getParent()->getLeft() != NULL){

    //     //set left child of parent to child of temp
    //         //check if child of temp is left or right
    //     if(temp->getLeft() != NULL){
    //         temp->getParent()->setLeft( temp->getLeft() );
    //     }
    //     else{
    //         temp->getParent()->setLeft( temp->getRight() );
    //     }

    //     //set parent of childs temp to parent of temp
    //     temp->getLeft()->setParent( temp->getParent() );
    // }
    // //right child
    // else{
    //     //check if temp child is right or left
    //     if(temp->getLeft() != NULL){
    //         temp->getParent()->setRight( temp->getLeft() );
    //     }
    //     else{
    //         temp->getParent()->setRight( temp->getRight() );
    //     }

    //     //set parent of childs temp to parent of temp
    //     temp->getRight()->setParent( temp->getParent() );
    // }

    // delete temp;
    // return;
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO

    //set temp node
    Node<Key,Value>* temp = current;

    //if left child exists
    if(temp->getLeft() !=  NULL){
        temp = temp->getLeft();

        //predecessor is right most node of left subtree
        while(temp->getRight() != NULL){
            temp = temp->getRight();
        }
        //once temp reaches right most-node return
        return temp;
    }
    else{
        //if no left-child (but right child of parent)
        if(temp->getParent() != NULL){
            if(temp == temp->getParent()->getRight()){
                return temp->getParent();
            }
        }
        
        //if no left-child (but left child of parent)
        //walk up ancestor chain until you find first right-child-pointer (parent is predecessor)
        while(temp->getParent() != NULL){
            //traverse upwards
            temp = temp->getParent();

            //if no parent then no successor
            if(temp->getParent() == NULL){
                return NULL;
            }

            //was the parent a right-child of its parent?
            if(temp == temp->getParent()->getRight()){
                //then parent is successor and return
                return temp->getParent();
            }
        }
        //if get to root w/o finding node who is a right child --> return NULL
        return NULL;
    }    
}

//successor helper function
template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    //set temp node
    Node<Key,Value>* temp = current;

    //if right child exists
    if(temp->getRight() !=  NULL){
        temp = temp->getRight();

        //successor is left most node of right subtree
        while(temp->getLeft() != NULL){
            temp = temp->getLeft();
        }
        //once temp reaches left most-node return
        return temp;
    }
    else{
        //if no right-child (but left child of parent)
        if(temp->getParent() != NULL)
        {
            if(temp == temp->getParent()->getLeft()){
                return temp->getParent();
            }
        }

        //no right-child (but right child of parent)
        while(temp->getParent() != NULL){
            
            //traverse upwards
            temp = temp->getParent();

            //if no parent then no successor
            if(temp->getParent() == NULL){
                return NULL;
            }

            //was the temp a left-child of its parent?
            if(temp == temp->getParent()->getLeft()){
                //then parent is successor and return
                return temp->getParent();
            }
        }
        //if get to root w/o finding node who is a right child --> return NULL
        return NULL;
    }    
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    //check if root is null you are done
    if(root_ == NULL){
        return;
    }
    //else start deleting
    trickleDownDelete(root_);

    //set root to null to reset
    root_ = NULL;

    // //start at smallest
    // Node<Key,Value>* temp = this->getSmallestNode();

    // //iterate through and delete
    // while(temp != NULL){
    //     //store successor before deleting
    //     Node<Key,Value>* successorTemp = successor(temp);

    //     //delete current node
    //     this->remove(temp->getKey());
        
    //     //iterate to successor
    //     temp = successorTemp;
    // }
    // return;
}

//trickleDownDelete (helper function for clear)
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::trickleDownDelete(Node<Key,Value>* next){
    //if there is a left node (explore)
    if(next->getLeft() != NULL){
        trickleDownDelete(next->getLeft());
    }
    //if there is a right node (explore)
    if(next->getRight() != NULL){
        trickleDownDelete(next->getRight());
    }
    //delete on way back up
    delete next;

}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    //set temp node to root
    Node<Key, Value>* temp = root_;

    //if root is NULL
    if(temp == NULL){
        return NULL;
    }

    //while left node exists
    while(temp->getLeft() != NULL){
        //traverse
        temp = temp->getLeft();
    }

    //traversed to left most node
    return temp;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    //set temp node to root
    Node<Key,Value>* temp = this->root_;

    //while temp node is not null
    while(temp != NULL){
        //check if equal -->
        if(temp->getKey() == key){
            return temp;
        }
        //if key less than
        else if (key < temp->getKey()){
            temp = temp->getLeft();
        }
        //key greater than
        else{
            temp = temp->getRight();
        }
    }

    return NULL;
    

}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    return nodeBalanced(root_);

//------------------------
    // //declare tracking bool
    // bool balanced = true;

    // //start at smallest
    // Node<Key,Value>* temp = this->getSmallestNode();

    // //iterate through tree (in-order) using functions
    // while(temp != NULL){
    //     //if not balanced
    //     if(!nodeBalanced(temp)){
    //         balanced = false;
    //     }
    //     //iterate to next node
    //     temp = successor(temp);
    // }
 
    // return balanced;
//---------------------------

    // bool isBalanced = true;
    // // TODO
    // Node<Key, Value>* temp = root_;

    // //1. check if root is balanced
    // if(!nodeBalanced(root_)){
    //     isBalanced = false;
    // }
    // temp = temp->getLeft();

    // //2. if leftsubtree check
    // while(temp != NULL){
    //     if(!nodeBalanced(temp)){
    //         isBalanced = false;
    //     }
    // }
    

    // return isBalanced;
}

//single node helper
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::nodeBalanced(Node<Key, Value>* root) const
{   
    //1. empty
    if(root == NULL){
        return true;
    }
    //2. leaf node
    else if (root->getLeft() == NULL && root->getRight() == NULL){
        return true;
    }
    //3. one or more children
    else {
        //recurses left
        bool left = nodeBalanced(root->getLeft());
        //recurses right
        bool right = nodeBalanced(root->getRight());

        int leftHeight;
        int rightHeight;
        int delta;

        //empty left tree
        if(root->getLeft() == NULL){
            leftHeight = 0;
        }
        else{
            leftHeight = depth(root->getLeft(), 1);
        }

        //empty right tree
        if(root->getRight() == NULL){
            rightHeight = 0;
        }
        else{
            rightHeight = depth(root->getRight(), 1);
        }
        
        //calculate delta
        delta = leftHeight - rightHeight;

        if( (delta > 1) || (delta < -1)){
            return false;
        }
        return left && right;
    }
    
}

//depth helper function for isBalanced
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::depth(Node<Key,Value>* root, int currHeight) const
{
    int leftHeight = currHeight;
    int rightHeight = currHeight;

    
    //1. if leaf node
    if(root->getLeft() == NULL && root->getRight() == NULL){
        return currHeight;
    }
    //2. left tree
    if(root->getLeft() != NULL){

        //recurse left
        leftHeight = depth(root->getLeft(), currHeight+1);
    }
    //3. right tree
    if(root->getRight() != NULL){

        //recurse right
        rightHeight = depth(root->getRight(), currHeight+1);
    }

    //return greatest height
    if(leftHeight > rightHeight){
        return leftHeight;
    }
    else {
        return rightHeight;
    }
}





template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
