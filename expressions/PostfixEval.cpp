#include "PostfixEval.h"
//Max_temp_vars is the amount of temporary variables an expression can use.
//if this is ever exceeded, an out of range exception will be thrown by the vector.
#define MAX_TEMP_VARS 15

namespace postfix
{
	std::vector<PostfixItem*>  PostfixEval::sm_tempVars;

	PostfixEval::PostfixEval(std::vector<PostfixItem*> p_toEval)
	{
		m_equation = p_toEval;

		//allocate temporary variables
		if (sm_tempVars.size() == 0)
		{
			for (int i = 0; i < MAX_TEMP_VARS; ++i)
			{
				sm_tempVars.push_back(new PostfixItem());
			}
		}
	}

	PostfixEval::~PostfixEval()
	{
		//Delete old items
		for (PostfixItem* p : m_equation)
		{
			if (p->m_type != op)
			{
				delete p;
			}
		}
	}

	void PostfixEval::setVariable(const std::string& p_name, const float* p_address)
	{
		m_variables[p_name] = p_address;
	}

	void PostfixEval::setEquation(std::vector<PostfixItem*>& p_equation)
	{
		//Delete old items
		for (PostfixItem* p : m_equation)
		{
			if (p->m_type != op)
			{
				delete p;
			}
		}

		//set new items
		m_equation = p_equation;
	}

	float PostfixEval::getResult(const float& p_total, const float& p_x, const float& p_y, const float& p_z, const float& p_delta)
	{
		//populate working stack
		std::vector<PostfixItem*> workingStack = m_equation;
		unsigned int tempVarUsed = 0;

		int place = 0;
		if (workingStack.size() > 2)
		{
			float lastResult = 0;
			while (workingStack.size() > 2)
			{
				PostfixItem* nextItem = workingStack[place];
				//get the next operator
				while (nextItem->m_type != PostfixItemType::op)
				{
					nextItem = workingStack[++place];
				}

				//evaluate the operator with the past two items
				float leftVal, rightVal;
				//switch item types for left val
				switch (workingStack[place - 2]->m_type)
				{
				case total:
					leftVal = p_total;
					break;
				case x:
					leftVal = p_x;
					break;
				case y:
					leftVal = p_y;
					break;
				case z:
					leftVal = p_z;
					break;
				case delta:
					leftVal = p_delta;
				default: //number
					//constant
					leftVal = workingStack[place - 2]->m_value;
					break;
				}
				//left item

				//right item
				switch (workingStack[place - 1]->m_type)
				{
				case total:
					rightVal = p_total;
					break;
				case x:
					rightVal = p_x;
					break;
				case y:
					rightVal = p_y;
					break;
				case z:
					rightVal = p_z;
					break;
				case delta:
					rightVal = p_delta;
				default: //number
						 //constant
					rightVal = workingStack[place - 1]->m_value;
					break;
				}

				lastResult = nextItem->m_operator->getResult(leftVal, rightVal);
				//replace the operator and the past two items with the result
				PostfixItem* result = sm_tempVars[tempVarUsed++];
				result->m_type = PostfixItemType::number;
				result->m_value = lastResult;
				workingStack[place - 2] = result;

				//erase operator and consumed number
				workingStack.erase(workingStack.begin() + place - 1, workingStack.begin() + place + 1);
				--place; //put the place back one, since we shifted
			}
			
			return lastResult;
		}
		else
		{
			//We just have to return the first item (no operation)
			switch (workingStack[0]->m_type)
			{
			case total:
				return p_total;
			case x:
				return p_x;
			case y:
				return p_y;
			case z:
				return p_z;
			case delta:
				return p_delta;
			default: //number
					 //constant
				return workingStack[0]->m_value;
			}
			
		}
	}
}