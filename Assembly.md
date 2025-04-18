### Static keyword



- For language code:

    `static int x = 5`

- Three address code is:

    ```
    x = 5
    .static x
    ```

- Assembly code is:


### For variables allocated to the stack

- For language code:
    ```
    {
    int x = 5;
    int y;
    char arr[20];
    ...
    }
    ```

- Three address code is:
    ```
    x = 5
    .push x 4 // Push size of int onto stack
    .push y 4
    .push arr 20
    ...
    .pop 28 // Remove the elements as they exit scope
    ```

    - Function declarations are not pushed to the stack
    

- Assembly code is:
    ```
    ```


### For STRING LITERALS :
- Ideally based on the way the string literal is defined, we decide wether to store on stack or heap
    ```
    char *s = "hello"; // This would be stored in the data segment (where static variables are stored)
    char s[] = "hello"; // This would be stored in the stack
    char *s = malloc(10); // This would be stored in the heap
    ```

- In the current implementation we always create a `char *` when we encounter a string. So for now it will always be stored in data segment. If we add the stack implementation we will store it in the stack. 