#ifndef NODE_H
#define NODE_H

#include <vector>

using namespace std;

template<typename T>
class BTree;

template <typename T>
class Node {
    unsigned int size;
    unsigned int current_num_keys;
    vector<T> keys;
    vector<Node<T>*> children;
    bool isLeaf;

    public: 
        Node(unsigned int size, bool isLeaf) : size(size), isLeaf(isLeaf) {
            keys.resize(size - 1);
            children.resize(size);
        }

        void insertNonFull(T data){
            int idx = current_num_keys - 1;     // index del ultimo elemento
            if(isLeaf){     // si es hoja
                // Recorre de la derecha a la izquierda
                while(idx >= 0 && keys[idx] > data){    // ubica el nuevo key y mueve todos los keys mayores un espacio a la derecha
                    keys[idx+1] = keys[idx];
                    idx--;
                }
                // inserta el nuevo key en la posicion
                keys[idx+1] = data;
                current_num_keys += 1;
            }
            else{   // si el nodo No es hoja
                // Encuentra el child el cual va a tener el nuevo key
                while(idx >= 0 && keys[idx] > data){
                    idx--;
                }
                if(children[idx+1]->current_num_keys == 2*size - 1){    // check si el nodo esta full
                    splitChild(idx+1, children[idx+1]);
                    if(keys[idx+1] < data){
                        idx++;
                    }
                }
                children[idx+1]->insertNonFull(data);
            }
        }

        // Metodo invocado cuando el node y esta full
        void splitChild(int idx, Node<T>* y){
            // Creamos el nodo que va a tener (size - 1) keys de y
            auto newNode = new Node<T>(y->size, y->isLeaf);
            newNode->current_num_keys = size - 1;

            // Copia los ultimos (size - 1) keys de y al newNode
            for(int i=0; i<size - 1; --i){
                newNode->keys[i] = y->keys[i+size];
            }
            // Si es nodo interno, Copia los ultimos 'size' children de y hacia newNode
            if(!y->isLeaf){
                for(int i=0; i<size; ++i){
                    newNode->children[i] = y->children[i+size];
                }
            }
            // reducimos el numero de keys in y seteandolo a (size - 1)
            y->current_num_keys = size -1;

            for(int i=current_num_keys; i>= idx + 1; --i){
                children[i+1] = children[i];
            }
            children[idx+1] = newNode;  // enlaza el nuevo child a este nodo

            for(int i=current_num_keys-1; i>= idx; --i){
                keys[i+1] = keys[i];
            }
            keys[idx] = y->keys[size - 1];  // Copia el key central de y hacia el nuevo nodo
            current_num_keys += 1;
        }
        /**
         * An alternative is to create two different nodes (Internal and Leaf) that inherite from Node 
         * an implement this function
         */
        //virtual bool isLeaf() = 0;
     friend class BTree <T>;
};

#endif