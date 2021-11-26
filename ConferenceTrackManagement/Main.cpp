#include <iostream>
#include <fstream>

#include "Main.h"
#include "AdditionalTypes.h"
#include "Talk.h"
#include "Session.h"
#include "Track.h"
#include "ConferenceManger.h"

int main() {
	ConferenceManager conference{};
	conference.ReadInputFile(std::ifstream("..\\talks.txt"));
	conference.SortTalksOnTracks();

	std::cout << conference;
}