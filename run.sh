#!/bin/bash

INPUT_DIR="input"
OUTPUT_DIR="output"

rm -rf "$OUTPUT_DIR"
rm -rf src/lexer
mkdir -p "$OUTPUT_DIR"

echo "Compiling generator.l with lex..."
flex  -o src/lex.yy.cc src/generator.l

echo "Compiling lex.yy.cc with g++..."
g++  src/lex.yy.cc -o src/lexer -lfl

echo "Running test cases from $INPUT_DIR and saving results to $OUTPUT_DIR..."
for input_file in "$INPUT_DIR"/*; do
    filename=$(basename -- "$input_file")  
    filename_no_ext="${filename%.*}"  
    filename_no_prefix="${filename_no_ext#input}"  
    output_file="$OUTPUT_DIR/output${filename_no_prefix}.txt" 

    src/lexer  "$input_file" > "$output_file"
done

echo "All test cases executed successfully!"
