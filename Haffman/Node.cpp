#include "Node.h"

#include <string>

#define ll long long

using namespace std;

Node::Node(int w, int left0, int right0, int used0, int symb0, string code0) {
    this->w = w;
    left = left0;
    right = right0;
    used = used0;
    symb = symb0;
    code = code0;
}

Node::Node() {
    w = 0;
    left = 0;
    right = 0;
    used = 0;
    symb = 0;
    code = "";
}