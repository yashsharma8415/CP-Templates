// Code for finding (x ^ y) % MOD using fast exponentiation.
// Time Complexity - O(log y).

int fpow(int x, int y) {
    int temp;
    if (y == 0)
        return 1;
    temp = fpow(x, y / 2);
    if (y % 2 == 0)
        return (temp * temp) % MOD;
    else
        return (x * ((temp * temp) % MOD)) % MOD;
}
