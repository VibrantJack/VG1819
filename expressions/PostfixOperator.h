#pragma once
namespace postfix
{
	/*
		Operators for postix operations.
		Needed to calculate expressions at runtime without parsing.
	*/

	class PostfixOperator
	{
	public:
		virtual float getResult(const float& p_left, const float& p_right) const =0;
	};

	//I know you told me to put classes in their own files, but I feel like these classes are so
	//simple that they do not need their own files.

	class PlusOperator : public PostfixOperator
	{
	public:
		float getResult(const float& p_left, const float& p_right) const { return (p_left + p_right); };
	};

	class MinusOperator : public PostfixOperator
	{
	public:
		float getResult(const float& p_left, const float& p_right) const { return (p_left - p_right); };
	};

	class MultiplyOperator : public PostfixOperator
	{
	public:
		float getResult(const float& p_left, const float& p_right) const { return (p_left * p_right); };
	};

	class DivideOperator : public PostfixOperator
	{
	public:
		float getResult(const float& p_left, const float& p_right) const { return (p_left / p_right); };
	};

	class PowerOperator : public PostfixOperator
	{
	public:
		float getResult(const float& p_left, const float& p_right) const { return pow(p_left, p_right); };
	};
}