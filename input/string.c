static int i;

int main(){

    char *str = "Hello, World!";

    scanf("%i\n", &i);

    int j = 0;
    while(i--) {
        j += i;
        break;
    }

    printf("%i\n", i);


    return 0;
}