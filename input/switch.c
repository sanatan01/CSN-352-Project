int main() {

    // Negative switch cases
    int a = -11;
    switch (a) {
        case 10:{
            printf("a is 10\n");
            break;
        }
        case -11:{
            printf("a is -11\n");
            break;
        }
        default:{
            printf("a is not 10 or -11\n");
            break;
        }
    }

    // Positive switch cases
    int b = 10;
    switch (b) {
        case 10:{
            printf("b is 10\n");
            break;
        }   
        case 11:{
            printf("b is 11\n");
            break;
        }
        default:{
            printf("b is not 10 or 11\n");
            break;
        }
    }

    // Default case
    int c = 12;
    switch (c) {
        case 10:{
            printf("c is 10\n");
            break;
        }
        default:{
            printf("c is not 10\n");
            break;
        }
    }

    return 0;
}