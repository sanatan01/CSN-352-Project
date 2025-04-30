int main(){
    union k {
        int s;
        short fs;
        long long g;
        // char f[50];
    };

    union k gus;
    gus.s = 5;
    gus.fs = 7;

    printf("gus.s is %i\n", gus.s);
    printf("gus.g is %i\n", gus.fs);

    return 0;
}