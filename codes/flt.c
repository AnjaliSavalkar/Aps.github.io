#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

// Function to compute modular exponentiation
// It returns (x^y) % p
long long mod_exp(long long x, long long y, long long p) {
    long long res = 1;
    x = x % p;  // Update x if it is more than or equal to p
    while (y > 0) {
        // If y is odd, multiply x with result
        if (y & 1) {
            res = (res * x) % p;
        }
        // y must be even now
        y = y >> 1; // y = y/2
        x = (x * x) % p; // Change x to x^2
    }
    return res;
}

// Function to compute modular inverse of a number
// using Fermat's Little Theorem
long long mod_inverse(long long a, long long p) {
    return mod_exp(a, p - 2, p);  // Fermat's Little Theorem: a^(p-1) ≡ 1 (mod p)
}

// Function to generate the RSA keys
void generate_rsa_keys(long long *public_key, long long *private_key, long long *n, long long p, long long q) {
    *n = p * q;  // n is the product of two primes
    long long phi = (p - 1) * (q - 1);  // Euler's Totient Function

    // Choose e such that 1 < e < phi and e is coprime with phi
    long long e = 2;
    while (e < phi) {
        if (gcd(e, phi) == 1) break;
        e++;
    }

    *public_key = e;

    // Compute d, the modular inverse of e modulo phi
    *private_key = mod_inverse(e, phi);
}

// Function to compute greatest common divisor
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to encrypt a message using RSA
long long encrypt(long long message, long long public_key, long long n) {
    return mod_exp(message, public_key, n);
}

// Function to decrypt a message using RSA
long long decrypt(long long cipher, long long private_key, long long n) {
    return mod_exp(cipher, private_key, n);
}

int main() {
    long long p = 61, q = 53;  // Two prime numbers for RSA
    long long n, public_key, private_key;

    // Generate the public and private keys
    generate_rsa_keys(&public_key, &private_key, &n, p, q);

    printf("Public Key: (%lld, %lld)\n", public_key, n);
    printf("Private Key: (%lld, %lld)\n", private_key, n);

    long long message = 65;  // Sample message (plain text)
    printf("Original Message: %lld\n", message);

    // Encrypt the message
    long long encrypted_message = encrypt(message, public_key, n);
    printf("Encrypted Message: %lld\n", encrypted_message);

    // Decrypt the message
    long long decrypted_message = decrypt(encrypted_message, private_key, n);
    printf("Decrypted Message: %lld\n", decrypted_message);

    return 0;
}
