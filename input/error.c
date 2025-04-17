int main() {
    int x = 10;
    float y = 2.5;
    int a = 5;
    int arr[3];

    // 1. Undeclared variable
    // x = z + 5;

    // 2. Type mismatch: assigning float to int pointer
    // int *ptr = y;

    // 3. Incompatible condition in if-statement (suspicious usage)
    if ("hello") {
        printf("This should not work.\n");
    }



    return 0;
}
