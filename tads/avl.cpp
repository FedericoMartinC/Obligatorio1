#ifndef AVL_TREE
#define AVL_TREE
#include <cassert>
#include <string>
#include <iostream>
using namespace std;

// based on: https://www.geeksforgeeks.org/avl-tree-set-1-insertion/

template <class T>
class AVL
{
private:
    class AVLNode
    {
    public:
        T element;
        string tituloLibro;
        bool habilitado;
        AVLNode *left;
        AVLNode *right;
        int height;
        AVLNode(T element, string titulo) : element(element), left(NULL), right(NULL), height(1), tituloLibro(titulo), habilitado(true) {}
    };
    int cantLibrosHa;

    int cantLibrosDes;

    AVLNode *root; // root of the tree

    // A utility function to get the height of the tree.
    // In case of an empty tree, it returns 0.
    int height(AVLNode *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return node->height;
    }

    // A utility function to right
    // rotate subtree rooted with y
    AVLNode *rightRotate(AVLNode *y)
    {
        AVLNode *x = y->left;
        AVLNode *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = std::max(height(y->left),
                             height(y->right)) +
                    1;
        x->height = std::max(height(x->left),
                             height(x->right)) +
                    1;

        // Return new root
        return x;
    }

    // A utility function to left
    // rotate subtree rooted with x
    AVLNode *leftRotate(AVLNode *x)
    {
        AVLNode *y = x->right;
        AVLNode *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = std::max(height(x->left),
                             height(x->right)) +
                    1;
        y->height = std::max(height(y->left),
                             height(y->right)) +
                    1;

        // Return new root
        return y;
    }

    // Get Balance factor of node N
    int getBalance(AVLNode *node)
    {
        if (node == NULL)
            return 0;
        return height(node->right) - height(node->left);
    }

    // Recursive function to insert a element
    // in the subtree rooted with node and
    // returns the new root of the subtree.
    AVLNode *insert(AVLNode *&node, T element, string titulo)
    {
        /* 1. Perform the normal BST insertion */
        if (node == NULL){
            this->cantLibrosHa++;
            return new AVLNode(element, titulo);
        }
        if (element < node->element){
            node->left = insert(node->left, element, titulo);
        }else if (element > node->element){
            node->right = insert(node->right, element, titulo);
        }else {
            node->tituloLibro=titulo;
            if (!node->habilitado){
               this->cantLibrosHa++;
                this->cantLibrosDes--;
                node->habilitado=true;
            }
            return node;
        }
            

        /* 2. Update height of this ancestor AVLnode */
        node->height = 1 + std::max(height(node->left),
                                    height(node->right));

        /* 3. Get the balance factor of this ancestor
            node to check whether this node became
            unbalanced */
        int balance = getBalance(node);

        // If this node becomes unbalanced, then
        // there are 4 cases

        // Left Left Case
        if (balance < -1 && element < node->left->element)
            return rightRotate(node);

        // Right Right Case
        if (balance > 1 && element > node->right->element)
            return leftRotate(node);

        // Left Right Case
        if (balance < -1 && element > node->left->element)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance > 1 && element < node->right->element)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }

    string contains(AVLNode *node, T element) {
        if(node == NULL) {
            return "libro_no_encontrado";
        }
        if(node->element == element) {
            if (node->habilitado){
                return node->tituloLibro + " " + "H";
            }else{
                return node->tituloLibro + " " + "D";
            }
        }
        else if(node->element > element) {
            return contains(node->left, element);
        }
        else {
            return contains(node->right, element);
        }
    }

    bool toggle(AVLNode *&node, T element){
        if(node == NULL){
            return false;
        }else if (node->element == element){
            if(node->habilitado){
                this->cantLibrosDes++;
                this->cantLibrosHa--;
                node->habilitado=false;
            }else if (!node->habilitado){
                this->cantLibrosDes--;
                this->cantLibrosHa++;
                node->habilitado=true;
            }
            return true;
        }else if (node->element > element){
            return toggle(node->left,element);
        }else{
            return toggle(node->right, element);
        }
    }

    string count(){
        return to_string(this->cantLibrosDes+this->cantLibrosHa) + " " + to_string(this->cantLibrosHa) + " " + to_string(this->cantLibrosDes);
    }

public:
    AVL() : root(NULL) , cantLibrosDes(0) , cantLibrosHa(0)  {}

    void add(T element, string titulo)
    {
        root = insert(root, element, titulo);
    }

    string find(T element){
        return this->contains(root, element);
    }

    bool toggle (T element){
        return this->toggle(root, element);
    }

    string getCount(){
        return count();
    }

};

#endif
