cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(SyntaxAnalyser LANGUAGES C CXX)

# Directories
set(SRC_DIR src)
set(INCLUDE_DIR include)
set(INPUT_DIR input)
set(OUTPUT_DIR output)

# Source files
set(BISON_SRC ${SRC_DIR}/mylang.y)
set(FLEX_SRC ${SRC_DIR}/lexer.l)
set(TAC_FLEX_SRC ${SRC_DIR}/tac.l)
set(TAC_BISON_SRC ${SRC_DIR}/tac.y)  # Added TAC parser source
set(SCANNER_SRC ${SRC_DIR}/scanner.cpp)
set(PARSING_SRCS 
    ${SRC_DIR}/symtab.cpp 
    ${SRC_DIR}/types.cpp  
    ${SRC_DIR}/expression.cpp 
    ${SRC_DIR}/tac.cpp
    ${SRC_DIR}/codegen.cpp
    ${SRC_DIR}/tacgen.cpp
    ${SRC_DIR}/utils.cpp
)

# Output files for Bison and Flex
set(BISON_OUTPUT_SRC ${SRC_DIR}/y.tab.c)
set(BISON_OUTPUT_HDR ${INCLUDE_DIR}/y.tab.h)
set(FLEX_OUTPUT_SRC ${SRC_DIR}/lex.yy.c)
set(TAC_FLEX_OUTPUT_SRC ${SRC_DIR}/lex.tac.c)
set(TAC_BISON_OUTPUT_SRC ${SRC_DIR}/tac.tab.c)  # Added TAC parser output
set(TAC_BISON_OUTPUT_HDR ${INCLUDE_DIR}/tac.tab.h)  # Added TAC parser header

# Optional debug flags
option(DEBUG "Enable debugging flags" OFF)

if(DEBUG)
    add_compile_definitions(_DEBUG_MODE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

# Include directories
include_directories(
    ${INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}  # Add this line to include the build's include directory
)

# Find Bison and Flex
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

# Main language parser (Bison)
BISON_TARGET(MyParser 
    ${BISON_SRC} 
    ${CMAKE_CURRENT_BINARY_DIR}/${BISON_OUTPUT_SRC}
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/${BISON_OUTPUT_HDR}
    COMPILE_FLAGS "-Wnone")

# TAC parser (Bison)
BISON_TARGET(TacParser
    ${TAC_BISON_SRC}
    ${CMAKE_CURRENT_BINARY_DIR}/${TAC_BISON_OUTPUT_SRC}
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/${TAC_BISON_OUTPUT_HDR}
    COMPILE_FLAGS "-Wnone")

# Flex targets
FLEX_TARGET(MyScanner ${FLEX_SRC} ${FLEX_OUTPUT_SRC})
FLEX_TARGET(TacScanner ${TAC_FLEX_SRC} ${TAC_FLEX_OUTPUT_SRC})

# Connect lexers with their respective parsers
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)
ADD_FLEX_BISON_DEPENDENCY(TacScanner TacParser)

# Add executable
add_executable(syntax_analyser
    ${SCANNER_SRC}
    ${FLEX_MyScanner_OUTPUTS}
    ${FLEX_TacScanner_OUTPUTS}
    ${BISON_MyParser_OUTPUT_SOURCE}
    ${BISON_TacParser_OUTPUT_SOURCE}  # Added TAC parser output
    ${PARSING_SRCS}
)

add_custom_target(run_tests
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/${OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -DINPUT_DIR=${CMAKE_SOURCE_DIR}/${INPUT_DIR}
                              -DOUTPUT_DIR=${CMAKE_SOURCE_DIR}/${OUTPUT_DIR}
                              -DEXECUTABLE=$<TARGET_FILE:syntax_analyser>
                              -P ${CMAKE_SOURCE_DIR}/run_tests.cmake
    DEPENDS syntax_analyser
    COMMENT "Running test cases from ${INPUT_DIR}"
)

# Set source file properties
set_source_files_properties(
    ${BISON_MyParser_OUTPUT_SOURCE}
    ${BISON_TacParser_OUTPUT_SOURCE}  # Added TAC parser output
    ${FLEX_MyScanner_OUTPUTS}
    ${FLEX_TacScanner_OUTPUTS}
    PROPERTIES LANGUAGE CXX
)

# Output directories
set_target_properties(syntax_analyser PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${SRC_DIR}
)

message(STATUS "Flex outputs: ${FLEX_MyScanner_OUTPUTS}")
message(STATUS "TAC Flex outputs: ${FLEX_TacScanner_OUTPUTS}")
message(STATUS "Bison outputs: ${BISON_MyParser_OUTPUT_SOURCE}")
message(STATUS "TAC Bison outputs: ${BISON_TacParser_OUTPUT_SOURCE}")  # Added debug info
