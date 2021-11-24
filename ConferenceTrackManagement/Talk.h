#pragma once
#include <string>

#include "AdditionalTypes.h"

class Talk {
public:
	// Initialize talk with input string in given format title duration or title lightning
	explicit Talk(std::string& inputString);

	std::string GetName() const { return name_; }
	int GetDuration() const { return duration_; }
	const TimeOfDay& GetStartingTime() const { return startingTime_; }
	TimeOfDay GetEndingTime() const { return startingTime_.AddMinutes(duration_); }
	void SetStartingTime(TimeOfDay time);

	// Output talk in format of starting time title duration
	friend std::ostream& operator<<(std::ostream& os, const Talk& talk);
private:
	std::string name_;
	int duration_;
	TimeOfDay startingTime_;
};