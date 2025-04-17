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