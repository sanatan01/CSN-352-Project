int add(int a, int b){
    if(a==0){
        // Teri maa kaaa
    }
    else{
        // Not teri maa kaaa
    }
    add(a+1,b);
}

int main() {
    // Basic arithmetic expressions

    int a,b,c,d,e,f,g;

    a = 5;
    b = 3;
    c = a + b;
    d = a - b;
    e = a * b;
    f = a / b;
    g = a % b;
    g = a + b * c - d / e;

    int bw_and, bw_or, bw_xor, bw_not, shift_left, shift_right;
    
    // Bitwise expressions
    bw_and = a & b;    // bitwise AND
    bw_or = a | b;    // bitwise OR
    bw_xor = a ^ b;    // bitwise XOR
    // bw_not = ~a;       // bitwise NOT
    shift_left = a << 2;
    shift_right = a >> 1;

    int logic_and, logic_or, logic_not;

    // Logical expressions
    logic_and = (a > b) && (b > 0);
    logic_or = (a < b) || (b < 0);
    logic_not = (a == b);

    int eq, neq, lt, gt, le, ge;

    // Relational expressions
    eq = (a == b);
    neq = (a != b);
    lt = (a < b);
    gt = (a > b);
    le = (a <= b);
    ge = (a >= b);

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



}
