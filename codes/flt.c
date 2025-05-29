#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

long long mod_exp(long long x, long long y, long long p) {
    long long res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1) {
            res = (res * x) % p;
        }
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

long long mod_inverse(long long a, long long p) {
    return mod_exp(a, p - 2, p);
}

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void generate_rsa_keys(long long *public_key, long long *private_key, long long *n, long long p, long long q) {
    *n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = 2;
    while (e < phi) {
        if (gcd(e, phi) == 1) break;
        e++;
    }
    *public_key = e;
    *private_key = mod_inverse(e, phi);
}

long long encrypt(long long message, long long public_key, long long n) {
    return mod_exp(message, public_key, n);
}

long long decrypt(long long cipher, long long private_key, long long n) {
    return mod_exp(cipher, private_key, n);
}

int main() {
    long long p = 61, q = 53;
    long long n, public_key, private_key;
    generate_rsa_keys(&public_key, &private_key, &n, p, q);

    printf("Public Key: (%lld, %lld)\n", public_key, n);
    printf("Private Key: (%lld, %lld)\n", private_key, n);

    long long message = 65;
    printf("Original Message: %lld\n", message);

    long long encrypted_message = encrypt(message, public_key, n);
    printf("Encrypted Message: %lld\n", encrypted_message);

    long long decrypted_message = decrypt(encrypted_message, private_key, n);
    printf("Decrypted Message: %lld\n", decrypted_message);

    return 0;
}
