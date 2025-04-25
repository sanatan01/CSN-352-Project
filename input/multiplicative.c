int main() {

    // Integer operations
    int a;
    int b = 5;
    a = b * 2;      // Multiplication
    int c = a / b;  // Division
    int d = a % b;  // Modulus

    // Float operations
    float fa = 1.5;
    float fb = 2.3;
    fa = fb * 1.5;        // Multiplication
    float fc = fa / fb;   // Division

    // Double operations
    double da = 3.14159;
    double db = 2.71828;
    da = db * 2.0;         // Multiplication
    double dc = da / db;   // Division

    // Long double operations
    long double lda = 1.23456789L;
    long double ldb = 9.87654321L;
    lda = ldb * 1.5L;           // Multiplication
    long double ldc = lda / ldb; // Division

    // Short operations
    short sa = 100;
    short sb = 200;
    sa = sb * 2;         // Multiplication
    short sc = sa / sb;  // Division

    // Boolean operations (treated as integers in calculations)
    bool ba = true;
    bool bb = false;
    ba = bb * true;       // Multiplication (1 * 0 = 0)
    bool bc = ba / (bb + 1); // Division (0 / 1 = 0)

    // Character operations (treated as integers in calculations)
    char ca = 'A';        // ASCII value 65
    char cb = 'C';        // ASCII value 67
    ca = cb * 2;          // Multiplication (67 * 2 = 134)
    char cc = ca / cb;    // Division (134 / 67 = 2)

    // Unsigned integer operations
    unsigned int ua = 10;
    unsigned int ub = 5;
    ua = ub * 3;         // Multiplication
    unsigned int uc = ua / ub; // Division

    // Mixing types (requires type conversion)
    int mi = 5;
    float mf = 2.5;
    double md = mi * mf;      // int * float → converted to double
    float mresult = md / mi;  // double / int → stored as float

}