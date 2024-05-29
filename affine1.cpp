#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

int oclitMoRong(int r0, int r1) {
	int r[100], q[100], s[100], t[100];
	memset(r, 1, sizeof(r));
	r[0] = r0;
	r[1] = r1;
	int i = 0;
	while (true) {
		q[i + 1] = r[i] / r[i + 1];
		r[i + 2] = r[i] % r[i + 1];
		if (i == 0) {
			s[0] = 1;
			t[0] = 0;
		} else if (i == 1) {
			s[1] = 0;
			t[1] = 1;
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

string encodeAffine(string banRo, int a, int b) {
	string banMa = "";
	int length = banRo.size();
	for (int i = 0; i < length; i++) {
		if (isupper(banRo[i])) {
			banMa += char(((a * (banRo[i] - 'A') + b) % 26) + 'A');
		} else {
			banMa += char(((a * (banRo[i] - 'a') + b) % 26) + 'a');
		}
	}
	return banMa;
}

string decodeAffine(string banMa, int a, int b) {
	string banRo = "";
	int length = banMa.size();
	int a_inv = oclitMoRong(26, a);
	int temp;
	for (int i = 0; i < length; i++) {
		if (isupper(banMa[i])) {
			temp = a_inv * (banMa[i] - 'A' - b);
			while (temp < 0) temp += 26;
			temp %= 26;
			banRo += char(temp) + 'A';
		} else {
			temp = a_inv * (banMa[i] - 'a' - b);
			while (temp < 0) temp += 26;
			temp %= 26;
			banRo += char(temp) + 'a';
		}
	}
	return banRo;
}


int main() {
	cout << decodeAffine(encodeAffine("attAcK", 5, 3), 5, 3);
	return 0;
}

