int main() {
    enum Color {
        A, B=7, C=9, D
    };

    enum Color ffg = B;

    int y = ffg;
    printf("ffg is %i\n", y);

    return 0;
}