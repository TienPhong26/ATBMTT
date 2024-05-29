#include <bits/stdc++.h>
using namespace std;

int detK(int a[2][2]) {
	// detk = ad - bc
	int detk = a[0][0] * a[1][1] - a[1][0]*a[0][1];
	while (detk < 0) detk += 26;
	return detk % 26;
}

int main() {
	int a[2][2];
	cout << "Nhap a = "; cin >> a[0][0];
	cout << "Nhap b = "; cin >> a[0][1];
	cout << "Nhap c = "; cin >> a[1][0];
	cout << "Nhap d = "; cin >> a[1][1];
	cout << "\nDET[A] = " << detK(a);
	
	// tim detk^-1 mod 26
	
	return 0;
}
/*
3
3
2
5
*/

