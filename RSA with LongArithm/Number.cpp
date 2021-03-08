#include <string>
#include <vector>
#include <algorithm>

#include "Number.h"

#define ll long long

using namespace std;

Number::Number(string &s)
{
    ll u = 1;
    if (s[0] == '-') {
        u = -1;
        s = s.substr(1, s.size() - 1);
    }
    for (ll i = 0;;i ++) {
        if ((i + 1) * LB >= s.length()) {
            digits.push_back(stoll(s.substr(0, (s.length() - (LB * i)))) * u);
            break;
        }
        digits.push_back(stoll(s.substr(s.length() - (i + 1) * LB, LB)) * u);
    }
}

Number::Number(ll n)
{
    if (n == 0) {
        digits.push_back(0);
    }
    while (n > 0) {
        digits.push_back(n % BASE);
        n /= BASE;
    }
}

Number::Number(vector <ll> &v)
{
    for (ll i : v) {
        digits.push_back(i);
    }
}

string Number::to_String()
{
    string s; s = s;
    string s1; s1 = s1;
    for (ll i = digits.size() - 1; i >= 0; i --) {
        s1 = to_string(getDigit(i));
        if (s1[0] == '-' && i != digits.size() - 1) {
            s1 = s1.substr(1, s1.size() - 1);
        }
        if (i != digits.size() - 1) {
            for (ll j = 0; j < LB - s1.size(); j++) {
                s += "0";
            }
        }
        s += s1;
    }
    if (s.empty()) {
        s = "0";
    }
    return s;
}

void Number::normalize()
{
    for (ll i = 0; i < digits.size(); i ++) {
        ll digit = this->getDigit(i);
        digits[i] = digit % BASE;
        if (i == digits.size() - 1) {
            digits.push_back(digit / BASE);
            break;
        }
        digits[i + 1] += digit / BASE;
    }
    for (ll i = digits.size() - 1; i > 0; i --) {
        if (getDigit(i) == 0ll) {
            digits.pop_back();
        }
        else {
            break;
        }
    }
    ll m = digits.size() - 1;
    for (ll i = 0; i < m; i ++) {
        if (this->getDigit(i) > 0 && this->getDigit(m) < 0) {
            digits[i + 1] += 1;
            digits[i] -= BASE;
        }
        if (this->getDigit(i) < 0 && this->getDigit(m) > 0) {
            digits[i + 1] -= 1;
            digits[i] += BASE;
        }
    }
    for (ll i = digits.size() - 1; i > 0; i --) {
        if (getDigit(i) == 0ll) {
            digits.pop_back();
        }
        else {
            break;
        }
    }
}

ll Number::getDigit(ll &i)
{
    if (i < digits.size()) {
        return digits[i];
    }
    return(0);
}

Number Number::sum(Number &that)
{
    ll m = 1;
    auto *n = new Number(m);
    n->digits.pop_back();
    for (ll i = 0; i <  max(this->digits.size(), that.digits.size()); i ++) {
        n->digits.push_back(this->getDigit(i) + that.getDigit(i));
    }
    n->normalize();
    return *n;
}

Number Number::dif(Number &that)
{
    ll m = -1;
    Number n = that.multDigit(m);
    return n.sum(*this);
}

void Number::addNullsLeft(ll &N)
{
    while (digits.size() < N) {
        digits.push_back(0);
    }
}

void Number::addNullsRight(ll &N)
{
    while (digits.size() < N) {
        digits.insert(digits.begin(), 0);
    }
}

Number Number::leftDigits(ll &l)
{
    vector <ll> v;
    for (ll i = 0; l > i; i ++) {
        v.push_back(digits[i]);
    }
    return Number(v);
}

Number Number::rightDigits(ll &l)
{
    vector <ll> v;
    for (ll i = digits.size() - l; i < digits.size(); i ++) {
        v.push_back(digits[i]);
    }
    return Number(v);
}

Number Number::multDigit(ll &digit)
{
    Number n(this->digits);
    for (ll i = 0; i < digits.size(); i++) {
        n.digits[i] *= digit;
    }
    n.normalize();
    return n;
}

void Number::print_digits()
{
    for (ll digit : digits) {
        cout << digit << " ";
    }
    cout << endl;
}

ll Number::min_even_len(Number &that)
{
    ll n = max(digits.size(), that.digits.size());
    if (n % 2 == 1) {
        n += 1;
    }
    return n;
}

Number Number::mult(Number &that)
{
    this->normalize();
    that.normalize();
    if (this->digits.size() == 1) {
        return that.multDigit(this->digits[0]);
    }
    if (that.digits.size() == 1) {
        return this->multDigit(that.digits[0]);
    }
    ll n = this->min_even_len(that);
    ll n2 = n / 2;
    addNullsLeft(n);
    that.addNullsLeft(n);
    Number p1 = rightDigits(n2); p1.normalize();
    Number p2 = leftDigits(n2); p2.normalize();
    Number p3 = that.rightDigits(n2); p3.normalize();
    Number p4 = that.leftDigits(n2); p4.normalize();
    Number A1 = p1.mult(p3); A1.normalize();
    Number A2 = p2.mult(p4); A2.normalize();
    Number p12 = p1.sum(p2);
    Number A3 = (p3.sum(p4)).mult(p12); A3.normalize();
    Number A4 = ((A3.dif(A1)).dif(A2)); A4.normalize();
    ll length1 =  A1.digits.size() + n;
    ll length2 = A4.digits.size() + n2;
    A1.addNullsRight(length1); A1.normalize();
    A4.addNullsRight(length2); A4.normalize();
    Number res = ((A1.sum(A4)).sum(A2)); res.normalize();
    return res;
}

ll Number::sign()
{
    ll n = 0;
    if (digits[0] < 0) {
        n = -1;
    }
    else {
        n = 1;
    }
    return n;
}

ll Number::leq(Number &that)
{
    this->normalize();
    that.normalize();
    if (sign() < that.sign()) {
        return -1;
    }
    if (sign() > that.sign()) {
        return 1;
    }
    if (digits.size() < that.digits.size()) {
        if (sign() == -1) {
            return 1;
        }
        else {
            return -1;
        }
    }
    if (digits.size() > that.digits.size()) {
        if (sign() == -1) {
            return -1;
        }
        else {
            return 1;
        }
    }
    for (ll i = digits.size() - 1; i >= 0; i --) {
        if (digits[i] < that.digits[i]) {
            return -1;
        }
        if (digits[i] > that.digits[i]) {
            return 1;
        }
    }
    return 0;
}

vector <Number> Number::div(Number &that)
{
    ll k = 1;
    if (sign() < 0 && that.sign() > 0) {
        k = -1;
        *this = this->multDigit(k);
    }
    if (sign() > 0 && that.sign() < 0) {
        k = -1;
        that = that.multDigit(k);
    }
    if (sign() < 0 && that.sign() < 0) {
        k = -1;
        *this = this->multDigit(k);
        that = that.multDigit(k);
        k = 1;
    }
    this->normalize();
    that.normalize();
    ll z = 0;
    vector <Number> res;
    Number a(z);
    if (digits.size() < that.digits.size()) {
        res.push_back(a);
        res.push_back(*this);
        return res;
    }
    Number ans(z);
    ll t = that.digits.size();
    a = rightDigits(t);
    ll i = t;
    while (i <= digits.size()) {
        if (a.leq(that) >= 0) {
            ll l = 0;
            ll r = BASE;
            ll m = 0;
            while (l != r - 1) {
                m = (l + r) / 2;
                if (that.multDigit(m).leq(a) <= 0) {
                    l = m;
                }
                else {
                    r = m;
                }
            }
            Number p(that.multDigit(l));
            ans.digits.push_back(l);
            a = a.dif(p);
            a.normalize();
        }
        if (i != digits.size()) {
            a.digits.insert(a.digits.begin(), digits[digits.size() - i - 1]);
            a.normalize();
        }
        i ++;
    }
    reverse(ans.digits.begin(), ans.digits.end());
    res.push_back(ans.multDigit(k));
    res.push_back(a.multDigit(k));
    return res;
}