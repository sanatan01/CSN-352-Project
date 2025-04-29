// int a =100;
// char c='b';
// short b = 0x1234;
// long long ll = 0x1234567890;
// float f = 0.5;
// double d = 1.0;
// long double ld = 2.0;
// int a1;
// char c1;
// short b1;
// long long l1;
// long wow = 30;
// float f1;
// double d1;
// long  double ld1;
// long wow1;

int manyArgs(int a, int b, int c, int d ){
    int x = a+b+c+d*2;
    return x;
}

int main(){
    // static int sa = 100;
    // static char sc = 'b';
    // static short sb = 0x1234;
    // static long long sll_static = 0x1234567890;
    // static float sf = 0.5;

    // int b=5;
    // int *a = &b;
    // int **c;
    // c = &a;

    // const int FINAL_VALUE = 5; // final constant value
    // int result =0;
    // for(int i=0;i<10; i++){
    //     result += i;
    // }

    // int restultfinal = 5;
    int a=5;

    float f = 5.5;

    int resultmany = manyArgs(a,a,a,5);

    int y = 66;
    
    int z = 90;

    printf("Result: %i %i %i %f", y, resultmany, y, f);


    // int a = 100;
    // int b = 10;

    // int c = a*b;
    // int d = c/b;

    // if(a>b){
    //     a=0;
    // }
    // else{
    //     a=1;
    // }

    // int final =a;
    // int final1 = c;
    // int final2 =d;

    // int *ptr;

    // ptr = &final;

    // *ptr = 1;

    // final1 = final +10;

    // // ptr = &final2;

    // int final4 =final1;

    // int nice3 = a;

    // int *c = &nice;
    // *c = 2;
    // *c = nice;
    // nice = -10;
    // nice = 10*100;
    // nice = !nice2;
    // nice = !100;
    // nice = ~nice2;
    // nice = ~0;
    // nice = *c;

    return 0;
}
