#pragma once
#include <string>

#include "AdditionalTypes.h"

class Talk {
public:
	Talk(std::string& inputString);

	std::string GetName() const { return name_; }
	int GetDuration() const { return duration_; }
	void SetStartingTime(TimeOfDay time);

	friend std::ostream& operator<<(std::ostream& os, const Talk& talk);
private:
	std::string name_;
	int duration_;
	TimeOfDay startingTime_;
};