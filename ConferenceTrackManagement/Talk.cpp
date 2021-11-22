#include "Talk.h"

Talk::Talk(std::string& inputString)
{
	name_ = inputString;

	// Find last space in string
	const auto pos = inputString.find_last_of(" \t");
	std::string durationString = inputString.substr(pos + 1); // Get string of duration
	if (isdigit(durationString.at(0))) // Extract minutes if there are digits
	{
		duration_ = std::stoi(durationString);
	}
	else // Otherwise it is a lightning talk with a duration of 5 minutes
		duration_ = 5; 
}

void Talk::SetStartingTime(TimeOfDay time)
{
	startingTime_ = time;
}

std::ostream& operator<<(std::ostream& os, const Talk& talk)
{
	os << talk.startingTime_ << " " << talk.name_ << "\n";

	// Return output stream
	return os;
}
