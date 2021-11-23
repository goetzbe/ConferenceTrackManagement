#pragma once
#include "Session.h"

class Track {
public:
	Track();

	Session& GetMorningSession() { return morningSession_; };
	Session& GetAfternoonSession() { return afternoonSession_; };
	// Output track: Output sessions with lunch break in between and networking event at the end
	friend std::ostream& operator<<(std::ostream& os, const Track& track);
private:
	Session morningSession_;
	Session afternoonSession_;
};