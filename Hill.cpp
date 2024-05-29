#include<bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
}

int oclitMoRong(int r0, int r1) {
    int r[100], q[100], s[100], t[100];
    memset(r, 1, sizeof(r));
    r[0] = r0; r[1] = r1;
    int i = 0;
    while (true) {
        q[i + 1] = r[i] / r[i + 1];
        r[i + 2] = r[i] % r[i + 1];
        if (i == 0) {
            s[0] = 1;
            t[0] = 0;
        }
        else if (i == 1) {
            s[1] = 0;
            t[1] = 1;
        }
        else {
            s[i] = s[i - 2] - q[i - 1] * s[i - 1];
            t[i] = t[i -2] - q[i - 1] * t[i - 1];
        }
        if (r[i + 2] == 0) break;
        else i++;
    }
    i++;
    s[i] = s[i - 2] - q[i - 1] * s[i - 1];
    t[i] = t[i -2] - q[i - 1] * t[i - 1];
    return t[i] > 0 ? t[i] : (t[i] + r0);
}

void tichMatrix(int p[2], int k[2][2], int res[2]) {
    for (int i = 0; i < 2; i++) {
        res[i] = 0;
        for (int j = 0; j < 2; j++) {
            res[i] += p[j] * k[j][i];
        }
        res[i] %= 26;
    }
}

string encryptHill(string banRo, int k[2][2]) {
    string banMa = "", s = banRo;
    for (int i = 0; i < banRo.size(); i++) banRo[i] = toupper(banRo[i]);
    for (int i = 0; i < banRo.size(); i += 2) {
        int p[2] = {banRo[i] - 'A', banRo[i + 1] - 'A'};
        int res[2];
        tichMatrix(p, k, res);
        banMa += char(res[0]) + 'A';
        banMa += char(res[1]) + 'A';
    }
    for (int i = 0; i < s.size(); i++) {
        if (islower(s[i])) banMa[i] = tolower(banMa[i]);
    }
    return banMa;
}

int detK(int k[2][2]) {
    int det = k[0][0] * k[1][1] - k[0][1] * k[1][0];
    while (det < 0) det += 26;
    return det % 26;
}

string decryptHill(string banMa, int k[2][2]) {
    string banRo = "", s = banMa;
    for (int i = 0; i < banMa.size(); i++) banMa[i] = toupper(banMa[i]);
    int tmp = oclitMoRong(26, detK(k));
    int pk[2][2] = {{k[1][1], -k[0][1]}, {-k[1][0], k[0][0]}};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            while (pk[i][j] < 0) pk[i][j] += 26;
            pk[i][j] *= tmp;
            pk[i][j] %= 26;
        }
    }
    for (int i = 0; i < banMa.size(); i += 2) {
        int c[2] = {banMa[i] - 'A', banMa[i + 1] - 'A'};
        int res[2];
        tichMatrix(c, pk, res);
        banRo += char(res[0]) + 'A';
        banRo += char(res[1]) + 'A';
    }
    for (int i = 0; i < s.size(); i++) {
        if (islower(s[i])) banRo[i] = tolower(banRo[i]);
    }
    return banRo;
}

int main() {
    int k[2][2];
    cout << "Nhap ma tran khoa k" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << "Nhap k[" << i << "][" << j << "] = ";
            cin >> k[i][j];
        }
    }

    cout << "Nhap ban ro: ";
    string banRo; cin >> banRo;
    cout << "Ban ma thu duoc la: " << encryptHill(banRo, k) << endl;

    cout << "Nhap ban ma: ";
    string banMa; cin >> banMa;
    cout << "Ban ro thu duoc la: " << decryptHill(banMa, k) << endl;
}

/*
1
0
2
7
sOnG
uUzQ
*/
