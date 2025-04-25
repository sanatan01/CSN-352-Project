int main()
{

    // Integer relational operations
    int a = 5, b = 10;
    bool int_less = a < b;       // Less than
    bool int_greater = a > b;    // Greater than
    bool int_equal = a == b;     // Equal to
    bool int_not_equal = a != b; // Not equal to

    // Float relational operations
    float fa = 1.5, fb = 2.3;
    bool float_less = fa < fb;       // Less than
    bool float_greater = fa > fb;    // Greater than
    bool float_equal = fa == fb;     // Equal to
    bool float_not_equal = fa != fb; // Not equal to

    // Double relational operations
    double da = 3.14159, db = 2.71828;
    bool double_less = da < db;       // Less than
    bool double_greater = da > db;    // Greater than
    bool double_equal = da == db;     // Equal to
    bool double_not_equal = da != db; // Not equal to

    // Long double relational operations
    long double lda = 1.23456789L, ldb = 9.87654321L;
    bool ldouble_less = lda < ldb;       // Less than
    bool ldouble_greater = lda > ldb;    // Greater than
    bool ldouble_equal = lda == ldb;     // Equal to
    bool ldouble_not_equal = lda != ldb; // Not equal to

    // Short relational operations
    short sa = 100, sb = 200;
    bool short_less = sa < sb;       // Less than
    bool short_greater = sa > sb;    // Greater than
    bool short_equal = sa == sb;     // Equal to
    bool short_not_equal = sa != sb; // Not equal to

    // Boolean relational operations
    bool ba = true, bb = false;
    bool bool_less = ba < bb;       // Less than
    bool bool_greater = ba > bb;    // Greater than
    bool bool_equal = ba == bb;     // Equal to
    bool bool_not_equal = ba != bb; // Not equal to

    // Character relational operations
    char ca = 'A', cb = 'C';        // ASCII values 65 and 67
    bool char_less = ca < cb;       // Less than
    bool char_greater = ca > cb;    // Greater than
    bool char_equal = ca == cb;     // Equal to
    bool char_not_equal = ca != cb; // Not equal to

    // Unsigned integer relational operations
    unsigned int ua = 10, ub = 5;
    bool uint_less = ua < ub;       // Less than
    bool uint_greater = ua > ub;    // Greater than
    bool uint_equal = ua == ub;     // Equal to
    bool uint_not_equal = ua != ub; // Not equal to

    // Mixing types relational operations
    int mi = 5;
    float mf = 2.5;
    bool mix_less = mi < mf;       // int < float
    bool mix_greater = mi > mf;    // int > float
    bool mix_equal = mi == mf;     // int == float
    bool mix_not_equal = mi != mf; // int != float

    return 0;
}