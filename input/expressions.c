int add(int a, int b) {
    return a + b;
}

void foo() {

    int** a;

    int** c = a;

    return;
}



int main() {
    int arr[5];

    char* cab = "hello";

    arr[3] = 5;
    // Basic arithmetic expressions
    int i;
    for (i = 0; i < 10; i += 1) {
        if (i == 5) {
            i = 6;
            break;
        }
        else {
            continue;
        }
    }

    for (i = 0; i < 10; i++) {
        if (i == 5) {
            i = 6;
            break;
        }
        else {
            continue;
        }
    }

    while (i == 0) {
        i += 2;
    }


    return i;

    int a, b, c, d, e, f, g;

    a = 5;
    b = 3;
    c = a + b;
    d = a - b;
    e = a * b;
    f = a / b;
    g = a % b;
    g = a + b * c - d / e;

    int kyun = 5;
    int* kyu = &kyun;


    // Bitwise expressions
    int bw_and = a & b;    // bitwise AND
    int bw_or = a | b;    // bitwise OR
    int bw_xor = a ^ b;    // bitwise XOR
    // bw_not = ~a;       // bitwise NOT
    // int shift_left = a << 2;
    // int shift_right = a >> 1;

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
    int x;
    x = a;
    x += b;
    x -= b;
    x *= a;
    x /= 2;

    //    Conditional (ternary) operator
    int cond;
    cond = (a > b) ? a : b;
    cond = (a > b) ? a : x;

    int za, zb;
    int res;
    res = add(za, zb);

    a = res++;
    int* bf;
    bf = &a;


    // Unary expressions
    int pre_inc, post_dec;
    pre_inc = ++a;
    post_dec = b--;


    // sizeof operator
    int size;
    size = sizeof(a);

    char* ptr1;

    za = ptr1[3];

    int arr1[100];
    zb = arr1[10];
    // Comma operator
    // int comma_expr = (a = 1, b = 2, a + b);

    // Function call expression (side-effect)
    int sum = add(a, b);

    // Mixed expression with nested assignment and ternary operator
    c = (a > 0) ? (a + b) : (b - a);

    // Combination of logical and bitwise expressions
    int mix = ((a & b) || (a ^ b)) ? 1 : 0;

    foo();
    int s;
    s = add(1, 2);

    int aaaloo = -100, bhaijaan(int a), chowmein = 10;

}