#ifndef NODE_H
#define NODE_H

#include <vector>
#include <queue>

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
            keys.resize(2*size - 1);
            children.resize(2*size);
            current_num_keys = 0;
        }

        Node* search(int k){
            int idx=0;
            while(idx < current_num_keys && k > keys[idx]){     // if K is greater than current key in the node go to the next key
                idx++;
            }
            if(keys[idx] == k){
                return this;
            }
            else if(isLeaf){
                return nullptr;
            }
            else{
                return children[idx]->search(k);    // Recursive call: go down to the child and search
            }
        }

        void traverse(){
            int idx;
            for(idx=0; idx<current_num_keys; ++idx){
                if(!isLeaf){    // if It is internal node then traverse the subtree rooted at childer[i] and after that print keys[i]
                    children[idx]->traverse();      // recursive call
                }
                cout << keys[idx] << " ";
            }
            // Finally print the subtree rooted with last child (the rightmost position child)
            if(!isLeaf){    // if it is internal node it has child
                children[idx]->traverse();
            }
        }

        // Validado
        void insertNonFull(T data){
            int idx = current_num_keys - 1;     // index del elemento de mas a la derecha (last element)
            if(isLeaf){     // si es hoja
                // Recorre de derecha a izquierda (empezando por el ultimo)
                // ubica la posicion del nuevo key y mueve todos los keys mayores un espacio a la derecha
                while(idx >= 0 && keys[idx] > data){
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
                // check si el child node esta full
                if(children[idx+1]->current_num_keys == 2*size - 1){    // if child is full then split
                    splitChild(idx+1, children[idx+1]);
                    // after split the middle key of children[i] went up and children[i] is splitted into two
                    // check again with the new key added in this node...which is going to have the new key
                    if(keys[idx+1] < data){
                        idx++;
                    }
                }
                children[idx+1]->insertNonFull(data);
            }
        }

        // Metodo invocado cuando el node y esta full
        void splitChild(int idx, Node<T>* y){
            cout << "Split Child \n";
            // Creamos el nodo que va a tener (size - 1) keys de y
            auto newNode = new Node<T>(y->size, y->isLeaf);
            newNode->current_num_keys = size - 1;

            // Copia los ultimos (size - 1) keys de y al newNode
            for(int i=0; i<size - 1; ++i){
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

            for(int i=this->current_num_keys; i>= idx + 1; --i){
                children[i+1] = children[i];
            }

            // enlaza el nuevo child a este nodo
            children[idx+1] = newNode;

            for(int i=current_num_keys-1; i>= idx; --i){
                keys[i+1] = keys[i];
            }
            keys[idx] = y->keys[size - 1];  // Copia el key central de y hacia el nuevo nodo
            current_num_keys += 1;
        }

        void killSelf(){
            if(!isLeaf){    // If is internal Node go down
                for(int i=0; i<children.size(); ++i){
                    if(children[i]){
                        children[i]->killSelf();
                    }
                }
            }
            delete this;    // if I arrived here is a Leaf, so delete it
        }

         void recorrerNodes() {
            queue<pair<Node<T>*, int>> next;
            next.push(pair<Node<T>*, int>(this, 0));

            while (!next.empty()) {
                auto temp = next.front();
                next.pop();

                temp.first->printIndexes(temp.second);

                for (int i = 0; i < temp.first->children.size(); i++) {
                    next.push(pair<Node<T>*, int>(temp.first->children[i], temp.second + 2));
                }

                cout << endl;
            }  
    }

    void printIndexes(int level) {
        cout << level << ": ";
        for (int i = 0; i < keys.size(); i++) {
            cout << keys[i] << " ";
        }
    }

     friend class BTree <T>;
};

#endif