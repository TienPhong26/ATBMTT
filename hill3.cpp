#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

int oclitMoRong(int r0, int r1) {
	int r[100], q[100], s[100], t[100];
	memset(r, 1, sizeof(r));
	r[0] = r0; r[1] = r1;
	int i = 0;
	while (true) {
		r[i + 2] = r[i] % r[i + 1];
		q[i + 1] = r[i] / r[i + 1];
		if (i == 0) {
			s[0] = 1;
			t[0] = 0;
		} else if (i == 1) {
			t[1] = 1;
			s[1] = 0;
		} else {
			s[i] = s[i - 2] - q[i - 1] * s[i - 1];
			t[i] = t[i - 2] - q[i - 1] * t[i - 1];
		}
		if (r[i + 2] == 0) break;
		else i += 1;
	}
	i += 1;
	s[i] = s[i - 2] - q[i - 1] * s[i - 1];
	t[i] = t[i - 2] - q[i - 1] * t[i - 1];
	return t[i] > 0 ? t[i] : (t[i] + r0);
}

int detK(int k[2][2]) {
	int temp = k[1][1] * k[0][0] - k[1][0] * k[0][1];
	while (temp < 26) temp += 26;
	return temp % 26;
}

void kNghichDao(int k[2][2], int res[2][2]) {
	/*	d -c
	   -b  a
	*/
	int pK[2][2] = {{k[1][1], -k[0][1]}, {-k[1][0], k[0][0]}};
	int det = oclitMoRong(26, detK(k));
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			res[i][j] = det * pK[i][j];
			while (res[i][j] < 0) res[i][j] += 26;
			res[i][j] %= 26;
		}
	}
}

int main() {
	int k[2][2];
	cout << "Nhap a = "; cin >> k[0][0];
	cout << "Nhap b = "; cin >> k[0][1];
	cout << "Nhap c = "; cin >> k[1][0];
	cout << "Nhap d = "; cin >> k[1][1];
	if (gcd(26, detK(k)) != 1) {
		cout << "Ma tran vua nhap khong thoa man!";
	} else {
		int res[2][2];
		kNghichDao(k, res);
		cout << "Ma tran giai ma la: " << endl;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				cout << res[i][j] << "  ";
			cout << endl;
		}
	}
	return 0;
}

