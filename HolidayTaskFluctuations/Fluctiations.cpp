#include "Fluctiations.h"

vector < vector <ld > > m;
int n;

void swap_str (int i, int j) {
    for (int q = 0; q < n + 1; q ++) {
        swap(m[i][q], m[j][q]);
    }
}

void perm_matrix (int num) {
    for (int i = num + 1; i < n; i ++) {
        if (m[i][num] != 0) {
            swap_str(i, num);
        }
    }
}

void div_str (int num, ld d, int ind) {
    for (int i = max(0, ind - 2); i <= ind + 1; i ++) {
        m[num][i] /= d;
    }
    m[num][n] /= d;
}

void conv_str (int num1, int num2, ld c) {
    for (int i = 0; i < n + 1; i ++) {
        m[num2][i] -= c * m[num1][i];
    }
}

vector <ld> Gaus_method () {
    n = N + 1;
    for (int i = 0; i < n; i ++) {
        if (m[i][i] == 0) perm_matrix(i);
        div_str(i, m[i][i], i);
        for (int j = max(0, i - 2); j <= min(n - 1, i + 2); j ++) {
            if (j != i) conv_str(i, j, m[j][i] / m[i][i]);
        }
    }
    vector <ld> res(n);
    for (int i = 0; i < n; i ++) {
        res[i] = m[i][n];
    }
    return res;
}

vector < vector <ld > > get_matrix(ld a, ld b, ld x0, ld v0, vector <ld>& f, vector <ld>& x) {
    vector < vector <ld> > res(N + 1, vector <ld>(N + 2));
    res[0][0] = 1;
    res[0][N + 1] = x0;
    res[1][0] = -1;
    res[1][1] = 1;
    res[1][N + 1] = v0 * dt;
    for (int i = 1; i < N; i ++) {
        res[i + 1][i - 1] = 1;
        res[i + 1][i] = -2 - a * dt + b * dt * dt;
        res[i + 1][i + 1] = 1 + a * dt;
        if (f.empty()) {
            res[i + 1][N + 1] = 0;
        }
        else {
            res[i + 1][N + 1] = (f[i] + b * x[i]) * dt * dt;
        }
    }
    return res;
}


vector <ld> Fluctiatins::Harmonic (ld b, ld x0, ld v0) {
    vector <ld> f;
    m = get_matrix(0, b, x0, v0, f, f);
    return Gaus_method();
}

vector <ld> Fluctiatins::Harmonic_friction (ld a, ld b, ld x0, ld v0) {
    vector<ld> f;
    m = get_matrix(a, b, x0, v0, f, f);
    return Gaus_method();
}

vector <ld> Fluctiatins::Harmonic_friction_g (ld a, ld b, ld x0, ld v0, vector <ld>& f, vector <ld>& x) {
    m = get_matrix(a, b, x0, v0, f, x);
    return Gaus_method();
}