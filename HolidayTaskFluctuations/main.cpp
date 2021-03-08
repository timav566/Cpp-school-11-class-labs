#include <bits/stdc++.h>
#include "Fluctiations.h"

using namespace std;

#define ld long double

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ld susp_w2, susp_v0, grav, ball_x0, ball_y0, ball_v0, ball_a, length;
    cin >> susp_w2 >> susp_v0 >> grav >> ball_x0 >> ball_y0 >> ball_v0;
    vector <ld> susp_x = Fluctiatins::Harmonic(susp_w2, 0, susp_v0);
    vector <ld> susp_a(susp_x.size());
    for (int i = 0; i < susp_x.size(); i ++) {
        susp_a[i] = susp_x[i] * susp_w2;
    }
    length = sqrt(ball_x0 * ball_x0 + ball_y0 * ball_y0);
    ball_a = grav / length;
    ball_x0 -= 0;
    ball_v0 -= susp_v0;
    vector <ld> ball_x = Fluctiatins::Harmonic_friction_g(0, ball_a, ball_x0, ball_v0, susp_a, susp_x);
    cout.precision(5);
    for (int i = 0; i < ball_x.size(); i ++) {
        cout << '(' << dt * i << ',' << ball_x[i] << ')';
        if (i != ball_x.size() - 1) {
            cout << "--";
        }
    }
    return 0;
}