#pragma once
#include <vector>

#include "Talk.h"

class Session {
public:
	Session(TimeOfDay startingTime, int durationInMinutes);

	int GetFreeMinutes() { return freeMinutes_; }
	void AddTalk(Talk* talk);

	friend std::ostream& operator<<(std::ostream& os, const Session& session);
private:
	TimeOfDay startingTime_;
	int durationInMinutes_;
	int freeMinutes_;
	std::vector<Talk*> talks_;
};