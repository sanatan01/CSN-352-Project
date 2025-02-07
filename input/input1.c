#include <stdio.h>

int main() {

    int num = 10;
    float _value = 3.14;
    char *str = "Hello, World!";

    
    int 3num = 20;          
    float 123a = 45.67;     

    
    int hex_num = 0x1A3F;
    long long_num = 1234567890UL;
    double sci_num = 1.23e-4;

    
    int invalid_hex = 0x1G3F;  
    int invalid_oct = 01238;   
    float invalid_float = 123a; 

    
    char *valid_str1 = "This is a valid string.";
    char *valid_str2 = "Another valid string with escape \\n";

    
    char *unterminated_str = "This string is not properly closed";

    // Valid operators
    int a = 5, b = 10;
    int sum = a + b;
    int diff = a - b;
    int prod = a * b;
    int quotient = a / b;
    int remainder = a % b;

    // Valid control structures
    if (sum > diff) {
        printf("Sum is greater than difference.\n");
    } else {
        printf("Difference is greater than sum.\n");
    }

    for (int i = 0; i < 5; i++) {
        printf("Loop iteration: %d\n", i);
    }

    return 0;
}