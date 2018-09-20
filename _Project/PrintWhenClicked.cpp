#include <iostream>
#include "PrintWhenClicked.h"

PrintWhenClicked::PrintWhenClicked(const glm::vec3& p_pointMin, const glm::vec3& p_pointMax, const std::string& p_message)
	: Clickable(p_pointMin, p_pointMax), m_message(p_message)
{

}

PrintWhenClicked::~PrintWhenClicked()
{

}

void PrintWhenClicked::onClick()
{
	std::cout << m_message << std::endl;
}