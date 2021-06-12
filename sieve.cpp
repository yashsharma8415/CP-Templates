// Code for finding all the prime numbers less than LIM.
// Time Complexity - O(LIM * log(log(LIM))).

bool prime[LIM];

void sieve() {
    memset(prime, true, sizeof(prime));
    for (int p = 2; p * p < LIM; p++)
        if (prime[p] == true)
            for (int i = p * p; i < LIM; i += p)
                prime[i] = false;
    prime[0] = prime[1] = false;
}
