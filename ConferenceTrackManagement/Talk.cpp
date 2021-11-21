#include "Talk.h"

Talk::Talk(std::string& inputString)
{
	const auto pos = inputString.find_last_of(" \t\n");

	name_ = inputString.substr(0, pos);

	std::string lengthString = inputString.substr(pos + 1);
	if (isdigit(lengthString.at(0)))
	{
		length_ = std::stoi(lengthString);
	}
	else
		length_ = 5;
}