#include <bits/stdc++.h>

using namespace std;

#define ld long double


#ifndef DIFFERENTIAL_EQUATIONS_FLUCTIATINS_H
#define DIFFERENTIAL_EQUATIONS_FLUCTIATINS_H

static ld dt = 1e-1;
static int N = 3000;

class Fluctiatins {
public:
    static vector <ld> Harmonic (ld a, ld x0, ld v0);
    static vector <ld> Harmonic_friction (ld a, ld b, ld x0, ld v0);
    static vector <ld> Harmonic_friction_g (ld a, ld b, ld x0, ld v0, vector <ld>& f, vector <ld>& x);
};


#endif //DIFFERENTIAL_EQUATIONS_FLUCTIATINS_H
