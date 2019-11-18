#include <iostream>

#include "btree.h"

using namespace std;

int main(int argc, char *argv[]) {
    //system("pause");
    BTree<int> treecampeon(3);
    treecampeon.insert(10);
    return EXIT_SUCCESS;
}