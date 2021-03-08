#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <fstream>
#include <cstddef>

#include "Node.h"

using namespace std;

#define ll long long
#define eb emplace_back
#define ff as first
#define ss as second

const int base = 256;
const int Size = 8;
const ll MAX = 9999999999;

ifstream bin;
ofstream bout;
ofstream bout1;
vector <Node> tree;
vector <string> symbCodes;
vector <pair <char, int>> omega;
char c, curByte;
unsigned char C;
ll M, bitCount;

void check () {
    for (int i = 0; i < omega.size(); i ++) {
        cout << omega[i].first << " " << omega[i].second << " " << tree[i].code << endl;
    }
}

void get_min (int i, pair<int, int>& min) {
    for (ll j = 0; j < i; j ++) {
        if (tree[j].w < min.first && tree[j].used == 0) {
            min = make_pair(tree[j].w, j);
        }
    }
    tree[min.second].used = 1;
}

char from_str(string s) {
    char ans = 0;
    for (int i = s.size() - 1; i >= 0; i --) {
        if (s[i] == '1') {
            ans += pow(2, s.size() - i - 1);
        }
    }
    return ans;
}

void out (string& buffer, char &z) {
    z = from_str(buffer.substr(0, Size));
    bout << z;
    buffer = buffer.substr(Size, buffer.size() - Size);
}

void codes(int &num) {
    if (tree[num].symb >= 0) {
        symbCodes[tree[num].symb] = tree[num].code;
        return;
    }
    tree[tree[num].left].code = (tree[num].code + "0");
    tree[tree[num].right].code = (tree[num].code + "1");
    codes(tree[num].left);
    codes(tree[num].right);
}

vector <Node> build_tree(vector <int> freq) {
    for (int i = 0; i < base; i ++) {
        if (freq[i] != 0) {
            tree.eb(Node(freq[i], -1, -1, 0, i, ""));
            omega.eb(make_pair(char(i), freq[i]));
        }
    }
    M = tree.size();
    pair <int, int> min1 = make_pair(MAX, -1);
    pair <int, int> min2 = make_pair(MAX, -1);
    for (ll i = M; i < 2 * M - 1; i ++) {
        min1 = make_pair(MAX, -1);
        min2 = make_pair(MAX, -1);
        get_min(i, min1);
        get_min(i, min2);
        tree.emplace_back(Node(min1.first + min2.first, min1.second, min2.second, 0, -1, ""));
    }
    for (int i = 0; i < base; i ++) {
        symbCodes.emplace_back("");
    }
    int start = tree.size() - 1;
    codes(start);
    return tree;
}

void encode () {
    bin.open("input.txt", ios_base::binary);
    vector <int> freq(base, 0);
    while (bin.get(c)) {
        freq[(int)c] ++;
    }
    bin.close();
    build_tree(freq);
    cout << M << endl;
    check();
    bout.open("output.txt", ios_base::binary);
    char z;
    ll t;
    z = M - 1;
    bout << z;
    string buffer = "";
    for (auto & i : omega) {
        z = i.first; bout << z;
        for (int j = 0; j < 4; j ++) {
            z = (i.second << (j * Size)) >> (3 * Size);
            bout << z;
        }
    }
    bin.open("input.txt", ios_base::binary);
    buffer = "";
    while (bin.get(c)) {
        buffer += symbCodes[c];
        while (buffer.size() >= Size) {
            out(buffer, z);
        }
    }
    if (buffer.size() != 0) {
        while (buffer.size() % Size != 0) {
            buffer += "0";
        }
        out(buffer, z);
    }
    bin.close();
    bout.close();
}

int getNextBit() {
    if (bitCount % Size == 0) {
        bin.get(curByte);
        bitCount = 0;
        C = curByte;
    }
    int res = (C >> (Size - 1));
    C <<= 1;
    bitCount ++;
    return res;
}

void decode () {
    bout1.open("output1.txt", ios_base::binary);
    bin.open("output.txt", ios_base::binary);
    bin.get(c); c++;
    int y = 0;
    char c1 = ' ';
    char c2 = ' ';
    unsigned char c3 = ' ';
    vector < int > freq1(base, 0);
    for (int i = 0; i < (int)c; i ++) {
        bin.get(c2);
        for (int j = 0; j < 4; j ++) {
            bin.get(c1);
            c3 = c1;
            y += (c3 << (Size * (3 - j)));
        }
        freq1[c2] = y;
        y = 0;
    }
    tree = vector <Node>();
    symbCodes = vector <string>();
    omega = vector <pair <char, int>>();
    M = 0;
    build_tree(freq1);
    ll len = 0;
    cout << M << endl;
    check();
    for (int i = 0; i < omega.size(); i ++) {
        len += omega[i].second;
    }
    ll cur = 2 * M - 2;
    ll count = 0;
    bitCount = 0;
    for (int i = 0; i < tree.size(); i ++) {
        cout << char(tree[i].symb) << " ";
    }
    cout << endl;
    while (count < len) {
        int bit = getNextBit();
        if (tree[cur].symb >= 0) {
            bout1 << (char)tree[cur].symb;
            count ++;
            cur = 2 * M - 2;
        }
        if (bit == 0) {
            cur = tree[cur].left;
        }
        else {
            cur = tree[cur].right;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    encode();
    decode();
    return 0;
}