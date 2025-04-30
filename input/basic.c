int addx(int a, int b) {
    return a + b;
}

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// int array_sum(int arr[], int size) {
//     int sum = 0;
//     for (int i = 0; i < size; i++) {
//         sum = sum + arr[i];
//     }
//     return sum;
// }

struct Point {
    int x;
    int y;
};

// int point_sum(struct Point *p) {
//     return p->x + p->y;
// }

int main() {
    int a = 5, b = 10;

    int result = addx(a, b);
    if (result != 15) {
        printf("Arithmetic test failed: %d\n", result);
    }

    int fact = factorial(5);
    if (fact != 120) {
        printf("Recursion test failed: %i\n", fact);
    }

    // int arr[5][2];
    // arr[2][1] = 5;
    // int x = arr[2][1];
    // printf("Array element is: %i\n", x);

    // int arr[5] = {1, 2, 3, 4, 5};
    // int arr_sum = array_sum(arr, 5);
    // if (arr_sum != 15) {
    //     printf("Array sum test failed: %d\n", arr_sum);
    //     return 1;
    // }

    // struct Point p;
    // p.x = 3;
    // p.y = 4;
    // // int p_sum = point_sum(&p);
    // int a
    // int p_sum = p.x + p.y;
    // if (p_sum != 7) {
    //     printf("Struct test failed: %i\n", p_sum);
    // }

    int value = 0;
    if (a < b) {
        value = 1;
    } else {
        value = 2;
    }
    if (value != 1) {
        printf("Branching test failed: %i\n", value);
    }

    printf("All tests passed successfully!\n");
    return 0;
}
