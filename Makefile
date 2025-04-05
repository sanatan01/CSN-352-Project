INPUT_DIR := input
OUTPUT_DIR := output

SRC_DIR := src
INCLUDE_DIR := include
BISON_SRC := $(SRC_DIR)/mylang.y
FLEX_SRC := $(SRC_DIR)/lexer.l
SCANNER_SRC := $(SRC_DIR)/scanner.cpp
BISON_OUT := $(SRC_DIR)/y.tab.c
BISON_HDR := $(INCLUDE_DIR)/y.tab.h
BISON_HDR_TMP := $(SRC_DIR)/y.tab.h
FLEX_OUT := $(SRC_DIR)/lex.yy.c
EXECUTABLE := $(SRC_DIR)/syntax_analyser
HEADERS := $(wildcard $(INCLUDE_DIR)/*.h)

# Additional source files for parsing phase
PARSING_SRCS := $(SRC_DIR)/symtab.cpp $(SRC_DIR)/types.cpp  $(SRC_DIR)/expression.cpp $(SRC_DIR)/tac.cpp

all:  clear clean build run

clear:
	clear
clean:
	@echo "Cleaning up output and generated files..."
	rm -rf $(OUTPUT_DIR)
	rm -rf $(EXECUTABLE)
	rm -f $(BISON_OUT) $(BISON_HDR) $(FLEX_OUT)
	mkdir -p $(OUTPUT_DIR)

build: $(BISON_OUT) $(FLEX_OUT)
	@echo "Compiling the generated C files with g++..."
	g++ -o $(EXECUTABLE) --std=c++17 $(SCANNER_SRC) $(FLEX_OUT) $(BISON_OUT) $(PARSING_SRCS) -I$(INCLUDE_DIR)

$(BISON_OUT) $(BISON_HDR_TMP): $(BISON_SRC)
	@echo "Compiling $(BISON_SRC) with bison..."
	bison -d -o $(BISON_OUT) $(BISON_SRC) --warnings=none
	@mv $(BISON_HDR_TMP) $(BISON_HDR)

$(FLEX_OUT): $(FLEX_SRC)
	@echo "Compiling $(FLEX_SRC) with flex..."
	flex -o $(FLEX_OUT) $(FLEX_SRC)

run:
	@echo "Running test cases from $(INPUT_DIR) and saving results to $(OUTPUT_DIR)..."
	@mkdir -p $(OUTPUT_DIR)
	@for input_file in $(INPUT_DIR)/*; do \
		filename=$$(basename -- "$$input_file"); \
		filename_no_ext=$${filename%.*}; \
		filename_no_prefix=$${filename_no_ext#input}; \
		test_dir=$(OUTPUT_DIR)/$${filename_no_ext}; \
		mkdir -p "$$test_dir"; \
		output_file=$$test_dir/output.txt; \
		error_file=$$test_dir/error.txt; \
		symtab_file=$$test_dir/symtab.txt; \
		tac_file=$$test_dir/tac.txt; \
		$(EXECUTABLE) "$$input_file" "$$symtab_file" "$$tac_file"> "$$output_file" 2> "$$error_file"; \
	done
	@echo "All test cases executed successfully!"

.PHONY: all clean build run