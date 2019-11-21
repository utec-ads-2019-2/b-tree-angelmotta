#include <iostream>

#include "btree.h"

using namespace std;

int main(int argc, char *argv[]) {
    //system("pause");
    BTree<int> treecampeon(3);
    cout << "Insert 10 \n";
    treecampeon.insert(10);
    cout << "Insert 20 \n";
    treecampeon.insert(20);
    cout << "Insert 5 \n";
    treecampeon.insert(5);
    cout << "Insert 6 \n";
    treecampeon.insert(6);
    cout << "Insert 12 \n";
    treecampeon.insert(12);
    cout << "Insert 30 \n";
    treecampeon.insert(30);
    treecampeon.print();
    cout << boolalpha << treecampeon.search(6) << '\n';
    cout << boolalpha << treecampeon.search(13) << '\n';
    return EXIT_SUCCESS;
}