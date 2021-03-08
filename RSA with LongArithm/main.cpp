#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Number.h"

#define ll long long

using namespace std;

Number n0(0);
Number n1(1);
Number n2(2);

Number POW (Number& a, Number &p, Number& n) {
    if (p.leq(n0) == 0) {
        return n1;
    }
    Number res = POW(a, p.div(n2)[0], n);
    res = res.mult(res).div(n)[1];
    if (p.div(n2)[1].leq(n1) == 0) {
        res = res.mult(a).div(n)[1];
    }
    return res;
}

void gcd(Number a, Number b ,vector <Number> &r) {
    if (a.leq(n0) != 0 && b.leq(n0) != 0) {
        r.push_back(a.div(b)[1]);
        return gcd(b, a.div(b)[1], r);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    srand(time(NULL));
    string arr_s[20] = { "16022236204009818131831320183", "1298074214633706835075030044377087",
                         "177635683940025046467781066894531",  "4125636888562548868221559797461449",
                       "66241160488780141071579864797", "265252859812191058636308479999999", "263130836933693530167218012159999999",
                       "1066340417491710595814572169", "19134702400093278081449423917", "6161791591356884791277",
                       "18446744082299486207", "59604644783353249", "523347633027360537213687137", "1066340417491710595814572169",
                       "689852631578947368421", "618970019642690137449562111", "162259276829213363391578010288127",
                       "2305843009213693951", "7369130657357778596659", "29043636306420266077" };
    vector <Number> arr;
    for (int i = 0; i < 20; i ++) {
        arr.push_back(Number(arr_s[i]));
    }
    ll r_index = (rand() % 20);
    Number p = arr[r_index];
    Number q = p;
    while (q.leq(p) == 0) {
        q = arr[rand() % 20];
    }
    Number n = q.mult(p);
    p.normalize();
    q.normalize();
    Number p1 = p.dif(n1);
    Number q1 = q.dif(n1);
    Number Fi = q1.mult(p1);
    r_index = (rand() % 20);
    Number e = arr[r_index];
    vector <Number> r;
    vector <Number> x;
    vector <Number> y;
    r.push_back(Fi);
    gcd(e, Fi, r);
    x.push_back(n0);
    y.push_back(n1);
    x.push_back(n1);
    y.push_back(n0);
    Number rn = n0;
    for (int i = 2; i < r.size() - 1; i++) {
        rn = r[i - 2].div(r[i - 1])[0];
        Number x_p = rn.mult(x[i - 1]);
        Number y_p = rn.mult(y[i - 1]);
        x.push_back(x[i - 2].dif(x_p));
        y.push_back(y[i - 2].dif(y_p));
    }
    Number d = x[x.size() - 1];
    while (d.leq(n0) < 0) {
        d = d.sum(Fi);
    }
    cout << "p = " << p.to_String() << endl;
    cout << "q = " << q.to_String() << endl;
    cout << "n = " << n.to_String() << endl;
    cout << "e = " << e.to_String() << endl;
    cout << "Fi(n) = " << Fi.to_String() << endl;
    cout << "d = " << d.to_String() << endl;
    string m;
    cin >> m;
    Number M(m);
    cout << "M = " << M.to_String() << endl;
    Number X = n1;
    X = POW(M, e, n);
    cout << "X = " << X.to_String() << endl;
    X = POW(X, d, n);
    cout << "answer = " << X.to_String() << endl;
    return 0;
}