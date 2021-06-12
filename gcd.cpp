// Code for finding gcd of a and b.
// Time Complexity - O(log max(a, b)).

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
