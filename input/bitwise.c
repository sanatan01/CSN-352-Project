int main()
{

    // Integer bitwise operations
    int a;
    int b = 5;
    a = b << 1;     // Left shift (equivalent to multiplying by 2)
    int c = a >> 1; // Right shift (equivalent to dividing by 2)
    int d = a & b;  // Bitwise AND

    // Unsigned integer bitwise operations
    unsigned int ua = 10;
    unsigned int ub = 5;
    ua = ub | 3;               // Bitwise OR
    unsigned int uc = ua ^ ub; // Bitwise XOR

    // Character bitwise operations (treated as integers)
    char ca = 'A';       // ASCII value 65
    char cb = 'C';       // ASCII value 67
    ca = cb & 0xF;       // Bitwise AND with mask
    char cc = ca | 0x10; // Bitwise OR with mask

    // Boolean bitwise operations (treated as integers)
    bool ba = true;
    bool bb = false;
    ba = bb & true;    // Bitwise AND (1 & 0 = 0)
    bool bc = ba | bb; // Bitwise OR (0 | 0 = 0)

    // Mixing types (requires type conversion)
    int mi = 5;
    unsigned int mf = 2;
    int md = mi & mf;               // int & unsigned int → result is int
    unsigned int mresult = md | mi; // int | int → stored as unsigned int
}
