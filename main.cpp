#include <iostream>

#include "btree.h"

using namespace std;

int main(int argc, char *argv[]) {
    //system("pause");
    BTree<int> treecampeon(3);
    treecampeon.insert(10);
    treecampeon.insert(20);
    treecampeon.insert(5);
    treecampeon.insert(6);
    treecampeon.insert(12);
    treecampeon.insert(30);
    treecampeon.print();
    return EXIT_SUCCESS;
}