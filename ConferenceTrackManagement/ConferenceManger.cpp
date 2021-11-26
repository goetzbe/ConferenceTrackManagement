#include "ConferenceManger.h"
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>

ConferenceManager::ConferenceManager()
{
    talks_ = std::vector<Talk>{};
    tracks_ = std::vector<Track>{};
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

void ConferenceManager::SortTalksOnTracks(std::ostream& os)
{
    // Calculate least number of tracks needed for talks
    int sum = 0;
    for (auto& talk : talks_)
    {
        sum += talk.GetDuration(); // Get sum of durations of all talks
    }
    int numOfTracks = static_cast<int>(std::ceil(sum / (180.f + 240.f))); // Divide by length of one track

    // Add calculated number of tracks and keep list of sessions
    std::vector<Session*> sessions;
    sessions.reserve(2 * numOfTracks);
    tracks_.reserve(numOfTracks);
    for (int i = 0; i < numOfTracks; i++)
    {
        // Crate new track
        tracks_.push_back(Track()); 

        // Add sessions to list
        sessions.push_back(tracks_.back().GetMorningSession());
        sessions.push_back(tracks_.back().GetAfternoonSession());
    }

    // Sort talks in descending order
    std::sort(talks_.begin(), talks_.end(), [](const Talk& lhs, const Talk& rhs) 
        {
            return lhs.GetDuration() > rhs.GetDuration();
        });

    for (auto& talk : talks_)
    {
        std::sort(sessions.begin(), sessions.end(), [](const Session* lhs, const Session* rhs)
            { return lhs->GetFreeMinutes() > rhs->GetFreeMinutes(); });

        SortTalkIntoSession(&talk, &sessions);
    }
}

void ConferenceManager::SortTalkIntoSession(Talk* talk, std::vector<Session*>* sessions)
{
    for (Session* session : *sessions)
    {
        if (talk->GetDuration() < session->GetFreeMinutes())
        {
            session->AddTalk(talk);
            return;
        }
    }
}

std::ostream& operator<<(std::ostream& os, ConferenceManager& conferenceManager)
{
    // Get latest ending of afternoon session for synchronized time to start Networking Event
    TimeOfDay timeNetworkingEvent;
    for (auto& track : conferenceManager.tracks_)
    {
        if (track.GetEndingTime() > timeNetworkingEvent)
            timeNetworkingEvent = track.GetEndingTime();
    }

    int counter = 1;
    for (auto& track : conferenceManager.tracks_)
    {
        // Set synchronized time for Networking Event
        track.SetTimeNetworkingEvent(&timeNetworkingEvent);

        // Output number of track
        os << "Track " << counter << "\n";
        // Output track
        os << track;
        os << "\n";

        track.SetTimeNetworkingEvent(nullptr);

        counter++;
    }
    return os;
}
