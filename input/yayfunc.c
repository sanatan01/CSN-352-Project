int addx(int a, int b) {

    if (b == 0) {
        return 1;
    }
    else {
        int x = b - 1;
        return a + addx(a, x);
    }
}

// float subx(float a, float b) {
//     return b;
// }


// void test_func() {
//     return;
// }

int main() {
    int a = 2;
    // int a = 5;
    int b = 3;
    int c = addx(a, b);
    // float d = subx(a, b);
    // test_func();

    // int d = a;
    return 0;
}
