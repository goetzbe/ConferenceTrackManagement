#include "Talk.h"

Talk::Talk(std::string& inputString)
{
	const auto pos = inputString.find_last_of(" \t\n");

	name_ = inputString;

	std::string durationString = inputString.substr(pos + 1);
	if (isdigit(durationString.at(0)))
	{
		duration_ = std::stoi(durationString);
	}
	else
		duration_ = 5;
}

void Talk::SetStartingTime(TimeOfDay time)
{
	startingTime_ = time;
}

std::ostream& operator<<(std::ostream& os, const Talk& talk)
{
	os << talk.startingTime_ << " " << talk.name_ << "\n";
	return os;
}
