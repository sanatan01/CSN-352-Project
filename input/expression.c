int main() {
    char a = 5;
    unsigned char *b = (unsigned char *)malloc(sizeof(unsigned char));
    *b = 5;

    if ( a == b) {
        return 1;
    } else {
        return 0;
    }
}