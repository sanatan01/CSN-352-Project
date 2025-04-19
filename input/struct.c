int main() {

    struct f {
        int x;
    };

    struct s {
        int uh : 7;
        short b;
        struct f* gsd;
    };

    struct s z;
    z.b = 5;
    int a = z.b;
    int c = z.gsd->x;
    z.gsd->x = 10;

    union k {
        int s;
        int fs;
        long long g;
        char f[50];
    };

    union k gus;
    gus.s = 5;
    gus.g = 7;

    enum Color {
        A, B=7, C=9, D
    } asdf;

    enum Color ffg = A;

    struct s *ks;
    ks->b = 5;

}