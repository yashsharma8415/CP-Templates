// Code for matrix exponentiation.
// Time Complexity - O(n ^ 3 * logy) where n is the size of matrix and y is power.

int n;

struct Matrix
{
    vector<vector<int>> m;

    Matrix()
    {
        m.resize(n);

        for (int i = 0; i < n; ++i)
            m[i].resize(n, 0);
    }

    Matrix operator * (const Matrix& other)
    {
        Matrix product;

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                product.m[i][j] = 0;

                for (int k = 0; k < n; ++k)
                    product.m[i][j] = (product.m[i][j] + m[i][k] * other.m[k][j]) % MOD;
            }
        }

        return product;
    }
};

Matrix fpow(Matrix x, int y)
{
    Matrix product;

    for (int i = 0; i < n; ++i)
        product.m[i][i] = 1;

    while (y > 0)
    {
        if (y % 2)
            product = product * x;

        x = x * x;
        y /= 2;
    }

    return product;
}
