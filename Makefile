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
PARSING_SRCS := $(SRC_DIR)/symtab.cpp $(SRC_DIR)/types.cpp  $(SRC_DIR)/expression.cpp 

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
	g++ -o $(EXECUTABLE) $(SCANNER_SRC) $(FLEX_OUT) $(BISON_OUT) $(PARSING_SRCS) -I$(INCLUDE_DIR)

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
		output_file=$(OUTPUT_DIR)/output$${filename_no_prefix}.txt; \
		error_file=$(OUTPUT_DIR)/error$${filename_no_prefix}.txt; \
		symtab_file=$(OUTPUT_DIR)/symtab$${filename_no_prefix}.txt; \
		$(EXECUTABLE) "$$input_file" "$$symtab_file " > "$$output_file" 2> "$$error_file"; \
	done
	@echo "All test cases executed successfully!"

.PHONY: all clean build run