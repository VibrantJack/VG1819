#pragma once
#include <vector>
#include <map>
//By Callum MacKenzie
#include <string>

#include "PostfixOperator.h"

//Evaluates a postfix expression.

namespace postfix
{
	enum PostfixItemType {op, number, total, x, y, z, delta};

	struct PostfixItem
	{
		PostfixItemType m_type;
		
		PostfixOperator* m_operator; // op type
		float m_value; //number type
		std::string m_name; //var type
	};

	class PostfixEval
	{
	private:
		std::vector<PostfixItem*> m_equation;
		std::map<std::string, const float*> m_variables;

		//for efficiency
		static std::vector<PostfixItem*> sm_tempVars;
	public:
		PostfixEval(std::vector<PostfixItem*> p_toEval);
		virtual ~PostfixEval();

		void setEquation(std::vector<PostfixItem*>& p_equation);
		void setVariable(const std::string& p_name, const float* p_address);
		float getResult(const float& p_total, const float& p_x, const float& p_y, const float& p_z, const float& p_deltaTime);
	};
}