#!/bin/bash

INPUT_DIR="input"
OUTPUT_DIR="output"

rm -rf "$OUTPUT_DIR"
rm -rf src/syntax_analyser
rm -f src/*.tab.* src/*.yy.c
mkdir -p "$OUTPUT_DIR"

echo "Compiling mylang.y with bison..."
bison -d -o src/y.tab.c src/mylang.y

echo "Compiling generator.l with flex..."
flex -o src/lex.yy.c src/lexer.l

echo "Compiling the generated C files with gcc..."
gcc -o src/syntax_analyser src/scanner.c src/lex.yy.c src/y.tab.c -lfl

echo "Running test cases from $INPUT_DIR and saving results to $OUTPUT_DIR..."
for input_file in "$INPUT_DIR"/*; do
    filename=$(basename -- "$input_file")
    filename_no_ext="${filename%.*}"
    filename_no_prefix="${filename_no_ext#input}"
    output_file="$OUTPUT_DIR/output${filename_no_prefix}.txt"
    error_file="$OUTPUT_DIR/error${filename_no_prefix}.txt"

    src/syntax_analyser "$input_file" > "$output_file" 2> "$error_file"
done

echo "All test cases executed successfully!"
