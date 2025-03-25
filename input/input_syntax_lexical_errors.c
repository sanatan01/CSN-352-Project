/* Test file with multiple errors to test error recovery */

// Lexical errors
int main() {
    int invalid@id = 10; // Invalid identifier
    int octal = 0789; // Invalid octal literal

    // Syntax errors - missing semicolons
    int x = 10
    int y = 20;
    
    // Invalid expressions
    int z = 5 + * 3;
    int a = (5 + );
    int b = 5 + + 6;
    
    // Missing parenthesis
    if (x > 5) {
        printf("x is greater than 5\n");
    }
    
    // Missing braces
    if (y < 10) 
        printf("y is less than 10\n");
        y = y + 1;
    
    // Function with error in declaration
    void function1(int a, int b,) {
        return a + b;
    }
    
    // Struct with errors
    struct Point {
        int x
        int y;
        int;  // Missing identifier
    };
    
    // Multiple errors in one line
    int m = 1, n = , p = 3;
    
    // Error in for loop
    for (int i = 0; i < 10 i++) {
        printf("%d\n", i);
    }
    
    // Error in nested expression
    int nested = 5 + (3 * (2 - ));
    
    // Error in array declaration
    int arr[10] = {1, 2, 3, , 5};
    
    // Error in function call
    printf("Hello", );
    
    // Multiple statement errors
    while (1) {
        break
        continue;
    }
    
    // Missing type specifier
    q = 25;
    
    // Type mismatch in assignment
    char* str2 = 123;
    
    // Error in return
    return 0
}

// Function definition errors
int add(int a, b) {  // Missing type for b
    return a + b;
}

// Mismatched braces
void test() {
    if (1) {
        printf("test");
    
    return;
}

// Dangling else
if (1)
    if (0)
        printf("Never");
    else
        printf("Always");
        
// Pointer errors
int ptr = &10;  // Address of literal
int* ptr2;
*ptr2 = 10;  // Dereferencing uninitialized pointer

// Multiple function prototype errors
int subtract(int, int,);
float divide(float a, );

// Enum errors
enum Colors {
    RED,
    GREEN,,
    BLUE,
};

char str[] = "This string is not terminated;

// Switch statement errors
int testSwitch(int code) {
    switch (code) {
        case 1:
            return 10;
        case:  // Missing value
            return 20;
        default
            return 0;
    }
}