# First clear the output directory to ensure fresh test results
file(REMOVE_RECURSE "${OUTPUT_DIR}")
file(MAKE_DIRECTORY "${OUTPUT_DIR}")

file(GLOB INPUT_FILES "${INPUT_DIR}/*")

foreach(input_file IN LISTS INPUT_FILES)
    get_filename_component(filename ${input_file} NAME)
    string(REPLACE "." ";" parts ${filename})
    list(GET parts 0 filename_no_ext)

    # Print the name of the file being processed
    message(STATUS "Running test case from ${filename}")

    set(test_dir "${OUTPUT_DIR}/${filename_no_ext}")
    file(MAKE_DIRECTORY ${test_dir})

    set(lexer_file "${test_dir}/lexer.txt")
    set(error_file "${test_dir}/error.txt")
    set(symtab_file "${test_dir}/symtab.txt")
    set(tac_file "${test_dir}/tac.txt")
    set(tac_lex_file "${test_dir}/tac_lex.txt")
    set(output_file "${test_dir}/debug.txt")
    set(assembly_file "${test_dir}/assembly.asm")

    execute_process(
        COMMAND ${EXECUTABLE} ${input_file} ${lexer_file} ${symtab_file} ${tac_file} ${tac_lex_file} ${assembly_file}
        OUTPUT_FILE ${output_file}
        ERROR_FILE ${error_file}
    )
endforeach()
