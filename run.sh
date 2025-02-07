#!/bin/bash

INPUT_DIR="input"
OUTPUT_DIR="output"

rm -rf "$OUTPUT_DIR"
mkdir -p "$OUTPUT_DIR"

echo "Compiling generator.l with lex..."
lex src/generator.l

echo "Compiling lex.yy.c with g++..."
g++ -o src/a.out src/lex.yy.c -lfl

echo "Running test cases from $INPUT_DIR and saving results to $OUTPUT_DIR..."
for input_file in "$INPUT_DIR"/*; do
    output_file="$OUTPUT_DIR/$test_name.txt"
    src/.a.out < "$input_file" > "$output_file"
done

echo "All test cases executed successfully!"
