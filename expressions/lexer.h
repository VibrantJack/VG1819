#pragma once
//Lexer converts a string into a serias of tokens (ints)
//so that parsing is easy.

namespace parser
{
	class Lexer
	{
	private:
		static bool sm_symSetup;
		
		//Members
		char m_lexbuf[BSIZE];
		std::string m_input;
		int m_place;

		int m_tokenVal;
		float m_fTokenVal;

		//Methods
		void createFloat(int p_startVal);
		int boolOpToTag(char first, char second, std::string& p_toSet);
	public:
		Lexer();
		~Lexer();

		void setInput(const std::string& p_input);
		int lexan(std::string& p_toSet);

		int getTokenVal() const { return m_tokenVal; }
		float getFTokenVal() const { return m_fTokenVal; }
	};
}