#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#ifndef LONGARITHMETICS_NUMBER_H

#define LONGARITHMETICS_NUMBER_H
#define ll long long

class Number {
public:
    ll BASE = 100000000;
    ll LB = 8;
    vector <ll> digits;
    explicit Number(string&);
    explicit Number(ll);
    explicit Number(vector <ll>&);
    Number sum(Number&);
    Number dif(Number&);
    Number leftDigits(ll&);
    Number rightDigits(ll&);
    Number multDigit(ll&);
    Number mult(Number&);
    vector <Number> div(Number&);
    string to_String();
    ll sign();
    ll getDigit(ll&);
    ll min_even_len(Number&);
    ll leq(Number&);
    void normalize();
    void addNullsLeft(ll&);
    void addNullsRight(ll&);
    void print_digits();
#endif //LONGARITHMETICS_NUMBER_H
};