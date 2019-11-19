#ifndef BTREE_H
#define BTREE_H

#include "node.h"

template <typename T>
class BTree {
    private:
        Node<T>* root;
        unsigned int degree;

    public:
        BTree(unsigned int degree) : degree(degree), root(nullptr) {};

        T search(int k) { 
            // TODO
        } 

        void insert(T data) {
            if(!root){
                root = new Node<T>(degree, true);   // for this first node isLeaf = True
                root->keys[0] = data;
                root->current_num_keys = 1;
            }
            else{   // if tree has at least one node
                if(root->current_num_keys == 2*degree-1){    // if root is full, then go up the midterm key
                    auto newRoot = new Node<T>(degree, false);    // now new root is Not Leaf
                    newRoot->children[0] = root;
                    newRoot->splitChild(0,root);      // split the original root and move up 1 key towards the new root
                    // ahora el root ya tiene 2 nodos hijos con espacio...con el insert identifica en cual nodo va la nueva key
                    int idx = 0;
                    if(newRoot->keys[0] < data){
                        idx++;
                    }
                    newRoot->children[idx]->insertNonFull(data);
                    root = newRoot; // Update the root to the new one
                }
                else{
                    root->insertNonFull(data);
                }
            }
        }

        bool remove(int k) {
            // TODO
        }

        void print() {
            if(root) root->traverse();
        }

        //~BTree();
};

#endif