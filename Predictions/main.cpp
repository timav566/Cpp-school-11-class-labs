#include <bits/stdc++.h>

using namespace std;

#define ld long double

vector < ld > m, pred0, pred1, pred2;
vector < vector <ld> > g2, g1, g0;
ld n_days, n_pred, N;

void swap_str (int i, int j, vector < vector <ld> >& g) {
    for (int q = 0; q <= N; q ++) {
        swap(g[i][q], g[j][q]);
    }
}

void perm_matrix (int num, vector < vector <ld> >& g) {
    for (int i = num + 1; i < N; i ++) {
        if (g[i][num] != 0) {
            swap_str(i, num, g);
        }
    }
}

void div_str (int num, ld d, vector < vector <ld> >& g) {
    for (int i = 0; i <= N; i ++) {
        g[num][i] /= d;
    }
}

void conv_str (int num1, int num2, ld c, vector < vector <ld> >& g) {
    for (int i = 0; i <= N; i ++) {
        g[num2][i] -= c * g[num1][i];
    }
}

vector <ld> Gaus_method (vector < vector <ld> >& g) {
    for (int i = 0; i < N; i ++) {
        if (g[i][i] == 0) perm_matrix(i, g);
        div_str(i, g[i][i], g);
        for (int j = 0; j < N; j ++) {
            if (j != i) conv_str(i, j, g[j][i] / g[i][i], g);
        }
    }
    vector <ld> res(N);
    for (int i = 0; i < N; i ++) {
        res[i] = g[i][N];
    }
    return res;
}

void get_matrix () {
    m.resize(n_days);
    m[0] = 2; m[1] = 3; m[2] = 3; m[3] = 3; m[4] = 4; m[5] = 13; m[6] = 13; m[7] = 17; m[8] = 17; m[9] = 20;
    m[10] = 20; m[11] = 28; m[12] = 45; m[13] = 59; m[14] = 63; m[15] = 90; m[16] = 114; m[17] = 147; m[18] = 199; m[19] = 253;
    m[20] = 306; m[21] = 367; m[22] = 438; m[23] = 495; m[24] = 658; m[25] = 840; m[26] = 1036; m[27] = 1264; m[28] = 1534; m[29] = 1836;
    m[30] = 2337; m[31] = 2777; m[32] = 3548; m[33] = 4149; m[34] = 4731; m[35] = 5389; m[36] = 6343; m[37] = 7497; m[38] = 8672; m[39] = 10313;
    m[40] = 11917; m[41] = 13584; m[42] = 15770; m[43] = 18328; m[44] = 21102; m[45] = 24490; m[46] = 27938; m[47] = 32008; m[48] = 36793; m[49] = 42853;
    m[50] = 47121; m[51] = 52763; m[52] = 57999; m[53] = 62773; m[54] = 68622; m[55] = 74588; m[56] = 80949; m[57] = 87147; m[58] = 93558; m[59] = 99399;
}

void k_2 () {
    vector <ld> f0, f1, f2, m0, m1, m2;
    m0 = m1 = m2 = m;
    ld x_i1_i1, x_i1_i2, x_i1_i3, x_i_i1, x_i2_i2, x_i2_i3, x_i_i2, x_i3_i3, x_i_i3;
    x_i1_i1 = x_i1_i2 = x_i1_i3 = x_i_i1 = x_i2_i2 = x_i2_i3 = x_i_i2 = x_i3_i3 = x_i_i3 = 0ll;
    for (int i = 3; i < n_days; i ++) {
        x_i1_i1 += m[i - 1] * m[i - 1];
        x_i1_i2 += m[i - 1] * m[i - 2];
        x_i1_i3 += m[i - 1] * m[i - 3];
        x_i_i1 += m[i] * m[i - 1];
        x_i2_i2 += m[i - 2] * m[i - 2];
        x_i2_i3 += m[i - 2] * m[i - 3];
        x_i_i2 += m[i] * m[i - 2];
        x_i3_i3 += m[i - 3] * m[i - 3];
        x_i_i3 += m[i] * m[i - 3];
    }
    g2 = vector < vector <ld> > (3, vector <ld>(4));
    g1 = vector < vector <ld> > (2, vector <ld>(3));
    g0 = vector < vector <ld> > (1, vector <ld>(2));
    g2[0][0] = x_i1_i1;
    g2[0][1] = x_i1_i2;
    g2[0][2] = x_i1_i3;
    g2[0][3] = x_i_i1;
    g2[1][0] = x_i1_i2;
    g2[1][1] = x_i2_i2;
    g2[1][2] = x_i2_i3;
    g2[1][3] = x_i_i2;
    g2[2][0] = x_i1_i3;
    g2[2][1] = x_i2_i3;
    g2[2][2] = x_i3_i3;
    g2[2][3] = x_i_i3;
    N = 3;
    f2 = Gaus_method(g2);
    pred2.resize(n_pred, 0);
    for (int i = 0; i < n_pred; i ++) {
        pred2[i] += f2[0] * m2[n_days + i - 1] + f2[1] * m2[n_days + i - 2] + f2[2] * m2[n_days + i - 3];
        m2.push_back(pred2[i]);
    }
    g1[0][0] = x_i1_i1;
    g1[0][1] = x_i1_i2;
    g1[0][2] = x_i_i1;
    g1[1][0] = x_i1_i2;
    g1[1][1] = x_i2_i2;
    g1[1][2] = x_i_i2;
    N = 2;
    f1 = Gaus_method(g1);
    pred1.resize(n_pred, 0);
    for (int i = 0; i < n_pred; i ++) {
        pred1[i] += f1[0] * m1[n_days + i - 1] + f1[1] * m1[n_days + i - 2];
        m1.push_back(pred1[i]);
    }
    g0[0][0] = x_i1_i1;
    g0[0][1] = x_i_i1;
    N = 1;
    f0 = Gaus_method(g0);
    pred0.resize(n_pred, 0);
    for (int i = 0; i < n_pred; i ++) {
        pred0[i] += f0[0] * m0[n_days + i - 1];
        m0.push_back(pred0[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("output.txt", "w", stdout);
    n_days = 60;
    n_pred = 10;
    get_matrix();
    k_2();
    cout << "k = 0" << endl;
    for (int i = 0; i < n_pred; i ++) {
        if (i == 0) {
            cout << 30.04 << ": ";
        }
        else {
            cout << 0 << i << ".05" << ": ";
        }
        cout << pred0[i] << endl;
    }
    cout << endl;
    cout << "k = 1" << endl;
    for (int i = 0; i < n_pred; i ++) {
        if (i == 0) {
            cout << 30.04 << ": ";
        }
        else {
            cout << 0 << i << ".05" << ": ";
        }
        cout << pred1[i] << endl;
    }
    cout << endl;
    cout << "k = 2" << endl;
    for (int i = 0; i < n_pred; i ++) {
        if (i == 0) {
            cout << 30.04 << ": ";
        }
        else {
            cout << 0 << i << ".05" << ": ";
        }
        cout << pred2[i] << endl;
    }
    cout << endl;
    return 0;
}