#pragma once
/**
  global.h
 **/

//Converted from C to C++

#include <ctype.h>     /* load character test routines */
#include <stdlib.h>
#include <string>


namespace parser
{
	#define BSIZE 128      
		/* buffer size */
	#define NONE   -1 
	#define EOS    '\0'

	#define ASSIGN 49
	#define PLUS 50
	#define MINUS 51
	#define STAR 52
	#define SLASH 53
	#define PERCENT 54
	#define COMMA 55

	#define EQ 100
	#define NOTEQ 101
	#define GT 102
	#define GTE 103
	#define LT 104
	#define LTE 105
	#define NOT 106
	#define BOOLAND 107
	#define BOOLOR 108

	#define REAL 255
	#define INTEGER 256
	#define IDENTIFIER 259
	#define OP 300
	#define CP 301
	#define SEMICOLON 302
	#define CURLYOP 303
	#define CURLYCLO 304

	#define TOTAL 350
	#define X_TOK 351
	#define	Y_TOK 352
	#define Z_TOK 353
	#define DELTA_TOK 354

	struct entry { /*  form of symbol table entry  */
		std::string lexname;
		int token;
	};

	static struct entry keywords[] = {
		"total", TOTAL,
		"TOTAL", TOTAL,
		"x", X_TOK,
		"X", X_TOK,
		"y", Y_TOK,
		"Y", Y_TOK,
		"z", Z_TOK,
		"Z", Z_TOK,
		"dt", DELTA_TOK,
		"DT", DELTA_TOK
	};
	static int lineno = 1;

	int insert(std::string lex, int tok);
	int lookup(std::string lex);

	//int throwError(char *m) /* generates all error messages */ {
	//   fprintf(stderr, "line %d: %s\n", lineno, m);
	//  exit(1); /* unsuccessful termination */
	//}

	#define error(str) do {fprintf(stderr, "Lexical Error at line %d: ", lineno); fprintf(stderr, str); exit(1);} while(0)

	//#define error(str) do {char errorstring[30]; sprintf(errorstring, str); throwError(errorstring);} while(0)



	extern struct entry symtable[]; /*  symbol table  */
}
