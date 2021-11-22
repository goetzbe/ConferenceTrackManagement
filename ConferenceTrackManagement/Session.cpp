#include "Session.h"

Session::Session(TimeOfDay startingTime, int durationInMinutes) 
	: startingTime_(startingTime), durationInMinutes_(durationInMinutes), freeMinutes_(durationInMinutes)
{
	talks_ = std::vector<Talk*>{};
}

void Session::AddTalk(Talk* talk)
{
	if (talks_.empty()) talk->SetStartingTime(startingTime_);
	else talk->SetStartingTime(talks_.back()->GetEndingTime());

	talks_.push_back(talk);
	freeMinutes_ -= talk->GetDuration();
}

std::ostream& operator<<(std::ostream& os, const Session& session)
{
	for(auto talk : session.talks_)
	{
		os << *talk;
	}
	return os;
}
