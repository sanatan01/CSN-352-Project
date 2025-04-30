
int multiple_params(int a, int b, int c, int d, int  e, int f, int g, int h, int i , int j, int k)
{
    int g = a + b + c + d + e + f + g+ h + i + j + k;
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

    int a = 10;
    int b = 12;
    int c = 13;
    int d = 14;
    int e = 25;
    int f = 26;
    int g = 27;
    int h = 28;
    int i = 29;
    int j = 30;
    int k = 31;

    int l = 31;
    int fxx = multiple_params(a, b, c, d, e, f, g, h, i, j, k);
    // int a = 10;
    // int b = 12;
    // int f = addx(a, b);
    printf("%i", fxx);
    // // test_func();

    // int d = a;
    return 0;
}
