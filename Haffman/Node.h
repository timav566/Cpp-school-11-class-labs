#include <string>

#ifndef HAFFMAN_NOTE_H
#define HAFFMAN_NOTE_H

using namespace std;

class Node {
public:
    int w;
    int left;
    int right;
    int used;
    int symb;
    string code;
    Node(int, int, int, int, int, string);
    Node();
};


#endif
