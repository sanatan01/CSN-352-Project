int add(int a, int b){
    if(a==0){
        // Teri maa kaaa
    }
    else{
        // Not teri maa kaaa
    }
    add(a+1,b);
    add(a*b,a/b);
    int i;
}

void foo(){
     return foo();
}

int main() {
    int arr[5];

    arr[3]=4;
    // Basic arithmetic expressions
    int i;
    for(i = 0; i < 10; i +=1 ) {
        if(i == 5) {
            i=6;
            break;
        }
        else {
            continue;
        }
    }

    

    return i;

    int a,b,c,d,e,f,g;

    a = 5;
    b = 3;
    c = a + b;
    d = a - b;
    e = a * b;
    f = a / b;
    g = a % b;
    g = a + b * c - d / e;
    
    // Bitwise expressions
    int bw_and = a & b;    // bitwise AND
    int bw_or = a | b;    // bitwise OR
    int bw_xor = a ^ b;    // bitwise XOR
    // bw_not = ~a;       // bitwise NOT
    int shift_left = a << 2;
    int shift_right = a >> 1;

    // Logical expressions
    int logic_and = (a > b) && (b > 0);
    int logic_or = (a < b) || (b < 0);
    int logic_not = (a == b);

    // Relational expressions
    int eq = (a == b);
    int neq = (a != b);
    int lt = (a < b);
    int gt = (a > b);
    int le = (a <= b);
    int ge = (a >= b);

    // // Assignment expressions and compound assignments
    long long x;
    x = a;
    x += b;
    x -= b;
    x *= a;
    x /= 2;

    // Conditional (ternary) operator
    int cond;
    cond = (a > b) ? a : b;
    cond = (a > b) ? a : x;

    int za;
    int zb;
    // zb=10;
    // za = *&zb;
    // -zb=5;

    int res;
    res=add(za,zb);
    // a=res++;
    // int* bf;
    // bf= &a;
    // za[0] = 1;

    // // Pointer expressions
    // int arr[10];
    // int *p;
    // p = arr;
    // p = p + 3;
    // int ptr_diff;
    // ptr_diff = p - arr;

    // // Unary expressions
    // int pre_inc, post_dec;
    // pre_inc = ++a;
    // post_dec = b--;

    // // Cast expression
    // double cast_expr;
    // cast_expr = (double)a;

    // // sizeof operator
    // int size;
    // size = sizeof(a);

    // char *ptr1;

    // int za,zb;

    // za = ptr1[3];

    // int arr1[];
    // zb = arr1[10];
    // Comma operator
    // int comma_expr = (a = 1, b = 2, a + b);

    // // Function call expression (side-effect)
    // int sum = add(a, b);

    // // Mixed expression with nested assignment and ternary operator
    // c = (a > 0) ? (a = 10, a + b) : (b = 20, a + b);

    // // Combination of logical and bitwise expressions
    // int mix;
    // mix = ((a & b) || (a ^ b)) ? 1 : 0;

    int lmnop = foo();


    int s;
    s = foo();


}
