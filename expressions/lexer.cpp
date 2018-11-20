
//Based on a Compiler Design class assignment
//hastily converted from C to C++

#include "global.h"
#include "lexer.h"

#include <math.h>
#include <cstdlib>

namespace parser
{
	bool Lexer::sm_symSetup = false;

	Lexer::Lexer()
	{
		/* loads keywords into symtable */ 
		if (!sm_symSetup)
		{
			sm_symSetup = true;
			struct entry *p;
			for (p = keywords; p->token; p++)
			{
				insert(p->lexname, p->token);
			}
		}
		
	}

	Lexer::~Lexer()
	{
		
	}

	void Lexer::setInput(const std::string& p_input)
	{
		m_input = p_input;
		m_place = 0;
	}

	void Lexer::createFloat(int p_startVal) {
		float fv = 0;
		int exponent = 1;
		int t = m_input[m_place++];
		while (isdigit(t)) {
			fv += (t - '0') * (1 / pow(10.0f, exponent));
			++exponent;
			t = m_input[m_place++];
		}
		fv += p_startVal;

		--m_place; //put last char back
		m_fTokenVal = fv;
	}


	int Lexer::boolOpToTag(char first, char second, std::string& p_toSet) {
		if (second == '=') { //is ?=
			switch (first) {
			case '<':
				p_toSet = "<=";
				return LTE;
			case '>':
				p_toSet = ">=";
				return GTE;
			case '!':
				p_toSet = "!=";
				return NOTEQ;
			case '=':
				p_toSet = "==";
				return EQ;
			}
		}
		else { //single character
			p_toSet = first;
			--m_place;
			switch (first) {
			case '<':
				return LT;
			case '>':
				return GT;
			case '!':
				return NOT;
			case '=':
				return ASSIGN;
			}
		}

		return NONE; //error
	}

	/*  lexical analyzer  */
	int Lexer::lexan(std::string& p_toSet) {

		int t;
		while (1) {
			t = m_input[m_place++];
			if (t == ' ' || t == '\t')
				; /*  strip out white space  */
			else if (t == '\n') {
				lineno = lineno + 1;
			}
			else if (isdigit(t)) { /* t is a digit */ 
				--m_place;
				std::string num;
				while (isdigit(m_input[m_place]))
				{
					num += m_input[m_place];
					++m_place;
				}
				int result = stoi(num);
				m_tokenVal = result;

				//check for float
				t = m_input[m_place++];
				if (t == '.') {
					createFloat(m_tokenVal);
					p_toSet = std::to_string(m_fTokenVal);
					return REAL;
				}
				//else, not float
				--m_place;
				p_toSet = std::to_string(m_tokenVal);
				return INT;
			}
			else if (t == '.') { //check for float starting with .
				createFloat(0);
				p_toSet = std::to_string(m_fTokenVal);
				return REAL;
			}
			else if (isalpha(t)) { /* t is a letter */
				int p, b = 0;
				while (isalnum(t)) { /* t is alphanumeric */
					m_lexbuf[b] = t;
					t = m_input[m_place++];
					b = b + 1;
					if (b >= BSIZE)
						error("Identifier too long. ");
				}
				m_lexbuf[b] = EOS;
				if (t != EOF)
					--m_place;
				p = lookup(m_lexbuf);
				if (p == 0)
					p = insert(m_lexbuf, ID);
				m_tokenVal = p;
				p_toSet = m_lexbuf;
				return symtable[p].token;
			}
			else if (t == EOF)
			{
				p_toSet = EOF;
				return EOF;
			}
			else {
				if (t == '<' || t == '>' || t == '=' || t == '!') { //t is bool op or assign
					int next = m_input[m_place++];

					if (next == '=') {//is '?='
						return boolOpToTag(t, next, p_toSet);
					}
					//else
					if (t != '=') {
						//bool op
						return boolOpToTag(t, next, p_toSet);
					}
					else //just '='
					{
					     //re-put read char
						--m_place;
						p_toSet = "=";
						return ASSIGN;
					}
				}
				//comments and '/'
				if (t == '/') {
					char next = m_input[m_place++];
					char afterNext = '0';
					switch (next) {
					case '/'://single line comment, discard until new line
						next = m_input[m_place++];
						while (next != '\n') {
							next = m_input[m_place++];
						}
						++lineno;
						return lexan(p_toSet);

					case '*': //block comment, discard until */
						next = m_input[m_place++];
						afterNext = m_input[m_place++];

						while (next != '*' && afterNext != '/') {
							if (next == '\n') {
								++lineno;
							}
							next = afterNext;
							afterNext = m_input[m_place++];
						}

						return lexan(p_toSet);

					default: //was just '/'
						--m_place;
						p_toSet = "/";
						return SLASH;
					}
				}
				//bool ops
				if (t == '|')
				{
					char next = m_input[m_place++];
					if (next == '|')
					{
						p_toSet = "||";
						return BOOLOR;
					}
					else
					{
						--m_place;
						p_toSet = t;
						return NONE;
					}
				}

				if (t == '&')
				{
					char next = m_input[m_place++];
					if (next == '&')
					{
						p_toSet = "&&";
						return BOOLAND;
					}
					else
					{
						--m_place;
						p_toSet = t;
						return NONE;
					}
				}

				// other single char symbols
				p_toSet = t;
				switch (t) {
				case '(':
					return OP;
				case ')':
					return CP;
				case ';':
					return SEMICOLON;
				case '+':
					return PLUS;
				case '-':
					return MINUS;
				case '*':
					return STAR;
				case '{':
					return CURLYOP;
				case '}':
					return CURLYCLO;
				case '%':
					return PERCENT;
				case ',':
					return COMMA;
				default:
					//arbitrary / unknown token
					m_tokenVal = NONE;
					return t;
				}
			}
		}
	}

}
