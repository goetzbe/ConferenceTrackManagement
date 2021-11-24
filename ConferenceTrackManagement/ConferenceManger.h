#pragma once
#include <vector>
#include <fstream>
#include <iostream>

#include "Talk.h"
#include "Track.h"

class ConferenceManager {
public:
	ConferenceManager();

	void ReadInputFile(std::ifstream input, std::ostream& os = std::cout);

	// Output whole Conference by track
	friend std::ostream& operator<<(std::ostream& os, const ConferenceManager& conferenceManager);
private:
	std::vector<Track> tracks_;
	std::vector<Talk> talks_;
};