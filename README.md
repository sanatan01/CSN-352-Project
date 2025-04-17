# CSN-352-Project

## TODO List

This lexer identifies correctly the following in a C++ code file

- All arithmetic and logical operator
- if-else
- for loop
- while loop
- do while loop
- switch cases
- array (integer and char)
- pointers
- structure
- printf and scanf
- function call with arguements
- goto, break and continue
- static keywords
- typedef
- until loop
- enum, union

## Steps to run

-  Add your test programs in `input/{filename}.c`
- Execute the following commands:

```
mkdir -p build
cmake -B build -G Ninja 
ninja -C build run_tests
```