#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern FILE* tac_in;
extern int tac_lineno;
extern int tac_lex(void);
