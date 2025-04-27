int main() {

    // Integer operations (already in your code)
    int a;
    int b = 5;
    a = b - 1;      // Subtraction
    int c = a - b;  // Subtraction with assignment

    // Float operations
    float fa = 1.5;
    float fb = 2.3;
    fa = fb + 0.7;        // Addition
    float fc = fa - fb;   // Subtraction

    // Double operations
    double da = 3.14159;
    double db = 2.71828;
    da = db + 1.0;         // Addition
    double dc = da - db;   // Subtraction

    // Long double operations
    long double lda = 1.23456789;
    long double ldb = 9.87654321;
    lda = ldb + 2.5;           // Addition
    long double ldc = lda - ldb; // Subtraction

    // Short operations
    short sa = 100;
    short sb = 200;
    sa = sb + 50;         // Addition
    short sc = sa - sb;   // Subtraction

    // Boolean operations (treated as integers in calculations)
    bool ba = true;
    bool bb = false;
    ba = bb + true;       // Addition (1 + 0 = 1)
    bool bc = ba - bb;    // Subtraction (true - false = true)

    // Character operations (treated as integers in calculations)
    char ca = 'A';        // ASCII value 65
    char cb = 'C';        // ASCII value 67
    ca = cb + 2;          // Addition (67 + 2 = 69, which is 'E')
    char cc = ca - cb;    // Subtraction ('E' - 'C' = 2)

    // Unsigned integer operations
    unsigned int ua = 10;
    unsigned int ub = 5;
    ua = ub + 15;         // Addition
    unsigned int uc = ua - ub; // Subtraction

    // Mixing types (requires type conversion)
    int mi = 5;
    float mf = 2.5;
    double md = mi + mf;      // int + float → converted to double
    float mresult = md - mi;  // double - int → stored as float

}