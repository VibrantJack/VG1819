#include "parser.h"
//Converted from C to C++
namespace parser
{
	Parser::Parser()
	{
		m_plusOP = new postfix::PlusOperator();
		m_minusOP = new postfix::MinusOperator();
		m_divideOP = new postfix::DivideOperator();
		m_multiplyOP = new postfix::MultiplyOperator();
		m_powOP = new postfix::PowerOperator();

		m_lexer = new Lexer();
	}

	Parser::~Parser()
	{
		//delete operators
		delete m_divideOP;
		delete m_minusOP;
		delete m_powOP;
		delete m_plusOP;
		delete m_multiplyOP;
	}

	std::vector<postfix::PostfixItem*> Parser::parse(const std::string& p_input)
	{
		m_lexer->setInput(p_input);
		m_toReturn.clear();
		m_lookahead = m_lexer->lexan(std::string());
		stmt();
		return m_toReturn;
	}

	void Parser::stmt() {
		expr();
	}

	void Parser::assign() {
		if (m_lookahead == ID) {
			const char* name = symtable[m_lexer->getTokenVal()].lexname.c_str();
			if (!match(ID)) {
				error("expected identifier");
			}
			if (!match(ASSIGN)) {
				error("expected '='");
			}

			expr();
			printf("<%s>=", name);
		}
		else {
			expr();
		}
	}

	void Parser::expr() {
		term();
		addsub();
	}

	void Parser::term() {
		factor();
		multdiv();
	}

	void Parser::addsub() {
		postfix::PostfixItem* item;
		switch (m_lookahead) {
		case PLUS:
			if (!match(PLUS)) { //these cases really shouldn't need to be checked, but it is OK
				error("expected '+'");
			}
			term();
			//Push +
			item = new postfix::PostfixItem();
			item->m_type = postfix::op;
			item->m_operator = m_plusOP;
			m_toReturn.push_back(item);
			//printf("+");
			addsub();

			return;

		case MINUS:
			if (!match(MINUS)) {
				error("expected '-'");
			}
			term();
			//Push -
			item = new postfix::PostfixItem();
			item->m_type = postfix::op;
			item->m_operator = m_minusOP;
			m_toReturn.push_back(item);
			//printf("-");
			addsub();

			return;

		default: //epsilon 
			return;
		}
	}

	void Parser::multdiv() {
		postfix::PostfixItem* item;

		switch (m_lookahead) {
		case STAR:
			if (!match(STAR)) {
				error("expected '*'");
			}
			factor();
			//Push *
			item = new postfix::PostfixItem();
			item->m_type = postfix::op;
			item->m_operator = m_multiplyOP;
			m_toReturn.push_back(item);
			//printf("*");
			multdiv();

			return;

		case SLASH:
			if (!match(SLASH)) {
				error("expected '/'");
			}
			factor();
			//Push /
			item = new postfix::PostfixItem();
			item->m_type = postfix::op;
			item->m_operator = m_divideOP;
			m_toReturn.push_back(item);
			//printf("/");
			multdiv();

			return;

		default: //epsilon
			return;
		}
	}

	void Parser::factor() {
		postfix::PostfixItem* item;

		switch (m_lookahead) {
		case OP:
			if (!match(OP)) {
				error("expected '('");
			}
			expr();
			if (!match(CP)) {
				error("expected ')'");
			}
			break;
		case INTEGER:
			//Push number
			item = new postfix::PostfixItem();
			item->m_type = postfix::number;
			item->m_value = m_lexer->getTokenVal();
			m_toReturn.push_back(item);
			//printf("[%d]", tokenval);
			if (!match(INTEGER)) {
				error("expected an int");
			}
			break;
		case TOTAL:
			//Push var
			item = new postfix::PostfixItem();
			item->m_type = postfix::total;
			item->m_name = "TOTAL";
			m_toReturn.push_back(item);
			//printf("<%s>", symtable[tokenval].lexname.c_str());
			if (!match(TOTAL)) {
				error("expected TOTAL");
			}
			break;
		case X_TOK:
			//Push var
			item = new postfix::PostfixItem();
			item->m_type = postfix::x;
			item->m_name = "X";
			m_toReturn.push_back(item);
			//printf("<%s>", symtable[tokenval].lexname.c_str());
			if (!match(X_TOK)) {
				error("expected x token");
			}
			break;
		case Y_TOK:
			//Push var
			item = new postfix::PostfixItem();
			item->m_type = postfix::y;
			item->m_name = "Y";
			m_toReturn.push_back(item);
			//printf("<%s>", symtable[tokenval].lexname.c_str());
			if (!match(Y_TOK)) {
				error("expected y token");
			}
			break;
		case Z_TOK:
			//Push var
			item = new postfix::PostfixItem();
			item->m_type = postfix::z;
			item->m_name = "Z";
			m_toReturn.push_back(item);
			//printf("<%s>", symtable[tokenval].lexname.c_str());
			if (!match(Z_TOK)) {
				error("expected z token");
			}
			break;
		case DELTA_TOK:
			item = new postfix::PostfixItem();
			item->m_type = postfix::delta;
			item->m_name = "delta_time";
			m_toReturn.push_back(item);
			//printf("<%s>", symtable[tokenval].lexname.c_str());
			if (!match(DELTA_TOK)) {
				error("expected DELTA token");
			}
			break;
		case REAL:
			//push number
			item = new postfix::PostfixItem();
			item->m_type = postfix::number;
			item->m_value = m_lexer->getFTokenVal();
			m_toReturn.push_back(item);
			//printf("[%.6f]", f_Tokenval);

			if (!match(REAL)) {
				error("expected a real");
			}
			break;
		default:
			error("syntax error, unknown token found");
		}
	}

	bool Parser::match(int t) {
		std::string result;
		if (m_lookahead == t) {
			m_lookahead = m_lexer->lexan(result);
			return true;
		}
		//else
		return false;
	}
}