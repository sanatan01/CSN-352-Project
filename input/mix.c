// // Typedef for a pointer to int
// typedef int* IntPtr;

// Enum for colors
enum Color { RED, GREEN, BLUE };

// Union for different data types
union Data {
    int intValue;
    float floatValue;
    char charValue;
};

// // Function with variable arguments
// int sum(int count, ...) {
//     va_list args;
//     va_start(args, count);

//     int total = 0;
//     for (int i = 0; i < count; i++) {
//         total += va_arg(args, int);
//     }

//     va_end(args);
//     return total;
// }

//int main(int argc, char* argv[])
int main() {
    // // --- Command line input ---
    // if (argc < 2) {
    //     cout << "Usage: " << argv[0] << " <filename>\n";
    //     return 1;
    // }
    // char filename[100];
    // strncpy(filename, argv[1], 99); // copy filename to char array
    // filename[99] = '\0'; // ensure null termination

    // // --- Dynamic memory allocation ---
    // IntPtr p = (IntPtr) malloc(5 * sizeof(int)); // using typedef for int*
    // if (!p) {
    //     cout << "Memory allocation failed!\n";
    //     return 1;
    // }
    // for (int i = 0; i < 5; i++) {
    //     p[i] = i * 10;
    // // }

    // cout << "Dynamically allocated array:\n";
    // for (int i = 0; i < 5; i++) {
    //     cout << p[i] << " ";
    // }
    // cout << endl;

    // free(p); // free dynamically allocated memory

    // --- Enum ---
    enum Color favorite = GREEN;
    if (favorite == GREEN) {
        printf("Favorite color is GREEN\n");
    }

    // --- Union ---
    // union Data d;
    // d.intValue = 100;
    // printf("Union int value: %i\n", d.intValue);
    // d.floatValue = 3.14f;
    // printf("Union float value: %f\n", d.floatValue);
    // d.charValue = 'A';
    // printf("Union char value: %c\n", d.charValue);
    // Note: Union only holds one value at a time!

    // // --- Var args ---
    // int total = sum(4, 10, 20, 30, 40);
    // // cout << "Sum using var args: " << total << endl;

    // // --- File manipulation ---
    // ofstream outfile(filename);
    // if (!outfile) {
    //     cout << "Failed to open file for writing.\n";
    //     return 1;
    // }
    // outfile << "Hello from C++ program!\n";
    // outfile << "Sum was: " << total << endl;
    // outfile.close();

    // cout << "Data written to file: " << filename << endl;

    return 0;
}

