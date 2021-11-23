#pragma once
#include <vector>

#include "Talk.h"

class Session {
public:
	Session(TimeOfDay startingTime, int durationInMinutes);

	int GetFreeMinutes() const { return freeMinutes_; }
	TimeOfDay GetEndingTime() const { return talks_.back()->GetEndingTime(); }

	void AddTalk(Talk* talk);

	// Output all talks in session in a seperate line
	friend std::ostream& operator<<(std::ostream& os, const Session& session);
private:
	TimeOfDay startingTime_;
	int durationInMinutes_;
	int freeMinutes_;
	std::vector<Talk*> talks_;
};