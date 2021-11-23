#include "Track.h"
#include "Session.h"

Track::Track() 
	: morningSession_(Session(TimeOfDay(9, 0, Period::AM), 180)),
	afternoonSession_(Session(TimeOfDay(1, 0, Period::PM), 240))
{}

std::ostream& operator<<(std::ostream& os, const Track& track)
{
	os << track.morningSession_;
	os << "12:00PM Lunch\n";
	os << track.afternoonSession_;
	TimeOfDay endingTime = track.afternoonSession_.GetEndingTime();
	if (endingTime.GetHours() < 4) endingTime = TimeOfDay(4, 0, Period::PM);
	os << endingTime << " Networking Event\n";

	// Return output stream
	return os;
}
