#include <stdio.h>
#include <string.h>

// Function to build the longest prefix-suffix (LPS) array
void computeLPSArray(char* pattern, int M, int* lps) {
    int length = 0;  // length of the previous longest prefix suffix
    lps[0] = 0;  // lps[0] is always 0
    int i = 1;

    // Build the LPS array
    while (i < M) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            // (pattern[i] != pattern[length])
            if (length != 0) {
                length = lps[length - 1];  // Try the previous possible prefix
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP search function
void KMPSearch(char* text, char* pattern) {
    int N = strlen(text);
    int M = strlen(pattern);

    // Create lps[] that will hold the longest prefix-suffix values for pattern
    int lps[M];
    computeLPSArray(pattern, M, lps);

    int i = 0;  // index for text[]
    int j = 0;  // index for pattern[]

    while (i < N) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == M) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < N && pattern[j] != text[i]) {
            // mismatch after j matches
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

// Driver program to test the KMP algorithm
int main() {
    char text[] = "Prime Video offers a variety of time traveler shows!";
    char pattern[] = "time traveler";

    printf("Searching for \"%s\" in the text...\n", pattern);
    KMPSearch(text, pattern);

    return 0;
}
