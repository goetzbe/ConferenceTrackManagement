#include <iostream>

#include "AdditionalTypes.h"
#include "Talk.h"
#include "Session.h"
#include "Track.h"

int main() {
	Track track = Track();

	Session& session1 = track.GetMorningSession();

	// Adding three talks to the session
	std::string inputString = "Writing Fast Tests Against Enterprise Rails 60min";
	Talk talk1 = Talk{ inputString };
	session1.AddTalk(&talk1);

	inputString = "Overdoing it in Python 45min";
	Talk talk2 = Talk{ inputString };
	session1.AddTalk(&talk2);

	inputString = "Lua for the Masses 30min";
	Talk talk3 = Talk{ inputString };
	session1.AddTalk(&talk3);

	Session& session2 = track.GetAfternoonSession();

	// Adding three talks to the session
	inputString = "Ruby Errors from Mismatched Gem Versions 45min";
	Talk talk4 = Talk{ inputString };
	session2.AddTalk(&talk4);

	inputString = "Common Ruby Errors 45min";
	Talk talk5 = Talk{ inputString };
	session2.AddTalk(&talk5);

	inputString = "Rails for Python Developers lightning";
	Talk talk6 = Talk{ inputString };
	session2.AddTalk(&talk6);


	std::string expected =
		"09:00AM Writing Fast Tests Against Enterprise Rails 60min\n"
		"10:00AM Overdoing it in Python 45min\n"
		"10:45AM Lua for the Masses 30min\n"
		"12:00PM Lunch\n"
		"01:00PM Ruby Errors from Mismatched Gem Versions 45min\n"
		"01:45PM Common Ruby Errors 45min\n"
		"02:30PM Rails for Python Developers lightning\n"
		"04:00PM Networking Event\n";

	std::cout << track;
}