#pragma once
#include <vector>

#include "global.h"

#include "expressions\lexer.h"
#include "expressions\PostfixEval.h"
#include "expressions\PostfixOperator.h"

//Parses a series of tokens and converts it into a postifx expression.
//coupled with PostfixEval class to make that class much more efficient

namespace parser
{
	class Parser
	{
	private:
		//Members
		std::vector<postfix::PostfixItem*> m_toReturn;
		int m_lookahead;

		postfix::PlusOperator* m_plusOP;
		postfix::MinusOperator* m_minusOP;
		postfix::MultiplyOperator* m_multiplyOP;
		postfix::DivideOperator* m_divideOP;
		postfix::PowerOperator* m_powOP;

		Lexer* m_lexer;

		//Helper methods (non-terminals of a grammar)
		void stmt(); void assign(); void expr(); void term();
		void addsub(); void multdiv(); void factor(); bool match(int t);
	public:
		Parser();
		virtual ~Parser();

		std::vector<postfix::PostfixItem*> parse(const std::string& p_input);
	};
}