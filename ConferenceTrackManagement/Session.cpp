#include "Session.h"

Session::Session(TimeOfDay startingTime, int durationInMinutes) 
	: startingTime_(startingTime), durationInMinutes_(durationInMinutes), freeMinutes_(durationInMinutes)
{
	talks_ = std::vector<Talk*>{}; // Initialize list of talks
}

void Session::AddTalk(Talk* talk)
{
	// if no talk in session yet, session starting time equals talk starting time
	if (talks_.empty()) talk->SetStartingTime(startingTime_);
	// otherwise ending time of last talk in session is starting time of next talk
	else talk->SetStartingTime(talks_.back()->GetEndingTime());

	// Add new talk to list of talks
	talks_.push_back(talk);
	// Calculate new remaining minutes
	freeMinutes_ -= talk->GetDuration();
}

std::ostream& operator<<(std::ostream& os, const Session& session)
{
	for(auto talk : session.talks_) // Output every talk in list of talks
	{
		os << *talk;
	}

	// Return output stream
	return os;
}
