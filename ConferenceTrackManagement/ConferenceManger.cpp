#include "ConferenceManger.h"
#include <sstream>
#include <string>
#include <iostream>

ConferenceManager::ConferenceManager()
{
}

void ConferenceManager::ReadInputFile(std::ifstream input, std::ostream& os)
{
    // Is a file to read from properly opened
    if (!input.is_open())
    {
        os << "No file opened!"; // Otherwise display error and return
        return;
    }

    std::string line;
    while (std::getline(input, line))
    {
        talks_.push_back(Talk(line)); // Read file by line and add as talk
    }

    for (auto& talk : talks_)
    {
        os << talk.GetName() << "\n"; // Display inital talks for user
    }
    os << "\n";
}

std::ostream& operator<<(std::ostream& os, const ConferenceManager& conferenceManager)
{
	// TODO: ^print out each track
    return os;
}
