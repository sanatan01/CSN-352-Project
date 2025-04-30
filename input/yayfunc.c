
int multiple_params(int a, int b, int c, int d, int e, int f)
{
    int g = a + b + c + d + e + f;
    return g;
}

float float_params(float a)
{
    return a;
}

int addx(int a, int b)
{
    if (b == 0)
    {
        return a;
    }

    return addx(a + 1, b - 1);
}

int main()
{

    int d = multiple_params(1, 2, 3, 4, 5, 6);
    int a = 10;
    int b = 12;
    int f = addx(a, b);
    printf("%i %i", d, f);
    // test_func();

    // int d = a;
    return 0;
}
