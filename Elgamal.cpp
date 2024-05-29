#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

using namespace std;

int gcd(int a, int b) {
    if (a < b) {
        return gcd(b, a);
    } else if (a % b == 0) {
        return b;
    } else {
        return gcd(b, a % b);
    }
}

long long power(long long a, long long b, long long c) {
    long long x = 1;
    long long y = a;
    while (b > 0) {
        if (b % 2 != 0) {
            x = (x * y) % c;
        }
        y = (y * y) % c;
        b = b / 2;
    }
    return x % c;
}

long long gen_key(long long q) {
    long long key = rand() % (q - 1) + 1; // generate a random number in the range [1, q-1]
    while (gcd(q, key) != 1) {
        key = rand() % (q - 1) + 1;
    }
    return key;
}

void encrypt(const string &msg, long long q, long long h, long long g, long long &p, long long *en_msg) {
    long long k = gen_key(q); // Private key for sender
    long long s = power(h, k, q);
    p = power(g, k, q);

    for (size_t i = 0; i < msg.size(); i++) {
        en_msg[i] = s * (long long)msg[i];
    }

    cout << "g^k used : " << p << endl;
    cout << "g^ak used : " << s << endl;
}

string decrypt(const long long *en_msg, size_t length, long long p, long long key, long long q) {
    string dr_msg;
    long long h = power(p, key, q);
    for (size_t i = 0; i < length; i++) {
        dr_msg += (char)(en_msg[i] / h);
    }
    return dr_msg;
}

int main() {
    srand(time(0));

    string msg = "encryption";
    cout << "Original Message: " << msg << endl;

    long long q = rand() % ((long long)pow(10, 20) - (long long)pow(10, 19)) + (long long)pow(10, 19);
    long long g = rand() % (q - 1) + 1;

    long long key = gen_key(q); // Private key for receiver
    long long h = power(g, key, q);
    cout << "g used: " << g << endl;
    cout << "g^a used: " << h << endl;

    size_t msg_len = msg.size();
    long long *en_msg = new long long[msg_len];
    long long p;
    encrypt(msg, q, h, g, p, en_msg);

    string dr_msg = decrypt(en_msg, msg_len, p, key, q);
    cout << "Decrypted Message: " << dr_msg << endl;

    delete[] en_msg; // Free the dynamically allocated memory

    return 0;
}

