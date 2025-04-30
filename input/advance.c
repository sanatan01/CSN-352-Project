// class Animal {
// protected:
//     string name; 
// public:
//     Animal(string n) : name(n) {}
//     void display() {
//         cout << "Animal Name: " << name << endl;
//     }
// };

// class Dog : public Animal {
// private:
//     int age; 
// public:
//     Dog(string n, int a) : Animal(n), age(a) {}

//     void bark() {
//         cout << name << " barks! Age: " << age << endl;
//     }
// };

// void greet() {
//     printf("Hello from function pointer!\n");
// }

// void callFunction(void (*func)()) {
//     func();
// }

int main() {
    // // --- Class, Object, Inheritance ---
    // Dog d("Buddy", 5);
    // d.display();      
    // d.bark();          

    // // --- Function Pointer ---
    // void (*fp)() = greet; 
    // callFunction(fp);    

    // --- References ---
    int x = 10;
    int* ref = &x;
    *ref = 20; 
    printf("Reference value: %i\n", x);

    // --- Multi-level Pointers ---
    int y = 50;
    int* p1 = &y;
    int** p2 = &p1;
    int*** p3 = &p2;
    printf("Multi-level pointer value: %i\n", ***p3);

    // // --- Multi-level Array ---
    // int arr[2][3] = { {1,2,3}, {4,5,6} };
    // printf("Multi-level array element arr[1][2]: %i\n", arr[1][2]);

    return 0;
}

