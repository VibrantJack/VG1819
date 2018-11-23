/**  
   symbol.c   
 ***********/

#include <string.h>
#include "global.h"

//Converted from C to C++ (barely)

namespace parser
{
	//This code is 99% from the Purple Dragon Book

	#define STRMAX 999    /* size of lexemes array */ 
	#define SYMMAX 100    /* size of symtable */

	char lexemes[STRMAX];
	int lastchar = -1; /* last used position in lexemes  */
	struct entry symtable[SYMMAX];

	int lastentry = 0; /* last used position in symtable */

	int lookup(std::string lex) /* returns position of entry for s */ {
		int p;
		for (p = lastentry; p > 0; p = p - 1)
			if (strcmp(symtable[p].lexname.c_str(), lex.c_str()) == 0) return p;
		return 0;
	}

	int insert(std::string lex, int tok) /* returns position of entry for s */ {
		int len;
		len = lex.size();
		if (lastentry + 1 >= SYMMAX)
			error("symbol table full");
		if (lastchar + len + 1 >= STRMAX)
			error("lexemes array full");
		lastentry = lastentry + 1;
		symtable[lastentry].token = tok;
		symtable[lastentry].lexname = &lexemes[lastchar + 1];
		lastchar = lastchar + len + 1;
		symtable[lastentry].lexname = lex;
		return lastentry;
	}
}