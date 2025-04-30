int main() {

    struct f {
        int x;
    };

    struct s {
        int uh;
        int b;
    };

    struct f ff;

    struct f* z1 = &ff;
    ff.x = 5;
    struct s z;
    z.b = 10;
    int a = z.b;
    z1->x = 15;
    int* xx = &(z.b);
    int f = *xx;
    printf("a is %i\n", f);
    int x = ff.x;
    printf("ff is %i\n", x);

    return 0;
}