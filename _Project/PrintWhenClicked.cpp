#include <iostream>
#include "PrintWhenClicked.h"

PrintWhenClicked::PrintWhenClicked(const glm::vec3& p_pointMin, const glm::vec3& p_pointMax, const std::string& p_message)
	: Clickable(p_pointMin, p_pointMax), m_message(p_message)
{

}

PrintWhenClicked::~PrintWhenClicked()
{

}

void PrintWhenClicked::setMessage(const std::string& p_message)
{
	m_message = p_message;
}

void PrintWhenClicked::onClick()
{
	std::cout << m_message << std::endl;
}

void PrintWhenClicked::onHoverStart()
{
	std::cout << "Started hovering!! (" << m_message << ")" << std::endl;
}

void PrintWhenClicked::onHoverEnd()
{
	std::cout << "Stopped hovering!! (" << m_message << ")" << std::endl;
}