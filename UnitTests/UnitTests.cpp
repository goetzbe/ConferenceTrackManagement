#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>
#include <fstream>

#include "AdditionalTypes.h"
#include "Talk.h"
#include "Session.h"
#include "Track.h"
#include "ConferenceManger.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(InitializingTests)
	{
	public:
		TEST_METHOD(InitalizeTalkWithMinutes)
		{
			std::string inputString = "Writing Fast Tests Against Enterprise Rails 60min";
			Talk talk = Talk{inputString};

			// Test
			Assert::AreEqual(std::string(inputString), talk.GetName());
			Assert::AreEqual(60, talk.GetDuration());
		}

		TEST_METHOD(InitalizeLightningTalk)
		{
			std::string inputString = "Rails for Python Developers lightning";
			Talk talk = Talk{inputString};

			// Test
			Assert::AreEqual(std::string(inputString), talk.GetName());
			Assert::AreEqual(5, talk.GetDuration());
		}
	};

	TEST_CLASS(OutputTests)
	{
	public:
		TEST_METHOD(OutputTimeOfDayNoLeadingZerosAM)
		{
			TimeOfDay time = TimeOfDay{ 10, 15, Period::AM };

			std::string expected = "10:15AM";

			// Output time
			std::stringstream buffer;
			buffer << time;

			// Test
			Assert::AreEqual(expected, buffer.str());
		}

		TEST_METHOD(OutputTimeOfDayWithLeadingZerosPM)
		{
			TimeOfDay time = TimeOfDay{ 3, 5, Period::PM };

			std::string expected = "03:05PM";

			// Output time
			std::stringstream buffer;
			buffer << time;

			// Test
			Assert::AreEqual(expected, buffer.str());
		}

		TEST_METHOD(OutputTalk)
		{
			std::string inputString = "Writing Fast Tests Against Enterprise Rails 60min";
			Talk talk = Talk{ inputString };
			talk.SetStartingTime(TimeOfDay(10, 15, Period::AM));

			std::string expected = "10:15AM Writing Fast Tests Against Enterprise Rails 60min\n";

			// Output talk
			std::stringstream buffer;
			buffer << talk;

			// Test
			Assert::AreEqual(expected, buffer.str());
		}

		TEST_METHOD(InitAndOutputSession)
		{
			Session session = Session{ TimeOfDay(9, 0, Period::AM), 180 };

			// Adding three talks to the session
			std::string inputString = "Writing Fast Tests Against Enterprise Rails 60min";
			Talk talk1 = Talk{ inputString };
			session.AddTalk(&talk1);

			inputString = "Overdoing it in Python 45min";
			Talk talk2 = Talk{ inputString };
			session.AddTalk(&talk2);

			inputString = "Lua for the Masses 30min";
			Talk talk3 = Talk{ inputString };
			session.AddTalk(&talk3);

			std::string expected = "09:00AM Writing Fast Tests Against Enterprise Rails 60min\n"
								   "10:00AM Overdoing it in Python 45min\n"
								   "10:45AM Lua for the Masses 30min\n";

			// Output session
			std::stringstream buffer;
			buffer << session;

			// Test
			Assert::AreEqual(expected, buffer.str());
			Assert::AreEqual(180 - 60 - 45 - 30, session.GetFreeMinutes());
		}

		TEST_METHOD(InitAndOutputTrack)
		{
			Track track = Track();

			Session& session1 = *track.GetMorningSession();

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

			Session& session2 = *track.GetAfternoonSession();

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

			// Output track
			std::stringstream buffer;
			buffer << track;

			// Test
			Assert::AreEqual(expected, buffer.str());
		}
	};

	TEST_CLASS(OperationTests)
	{
	public:
		TEST_METHOD(AddMinutesToTime)
		{
			TimeOfDay time = TimeOfDay(10, 15, Period::AM);
			time = time.AddMinutes(30);

			std::string expected = "10:45AM";

			// Output time
			std::stringstream buffer;
			buffer << time;

			// Test
			Assert::AreEqual(expected, buffer.str());
		}

		TEST_METHOD(AddMinutesToTimeChangeOfPeriod)
		{
			TimeOfDay time = TimeOfDay(11, 45, Period::AM);
			time = time.AddMinutes(30);

			std::string expected = "12:15PM";

			// Ouput time
			std::stringstream buffer;
			buffer << time;

			// Test
			Assert::AreEqual(expected, buffer.str());

			// Go from 12 to 01 PM
			time = time.AddMinutes(60);

			expected = "01:15PM";

			// Output time
			buffer.str("");
			buffer << time;

			// Test
			Assert::AreEqual(expected, buffer.str());
		}

		TEST_METHOD(ReadInputFileOfTalks)
		{
			std::stringstream buffer;

			ConferenceManager conference;
			// Read input file and write results into buffer
			conference.ReadInputFile(std::ifstream("..\\..\\talks.txt"), buffer);

			std::string expected =
				"Writing Fast Tests Against Enterprise Rails 60min\n"
				"Overdoing it in Python 45min\n"
				"Lua for the Masses 30min\n"
				"Ruby Errors from Mismatched Gem Versions 45min\n"
				"Common Ruby Errors 45min\n"
				"Rails for Python Developers lightning\n"
				"Communicating Over Distance 60min\n"
				"Accounting-Driven Development 45min\n"
				"Woah 30min\n"
				"Sit Down and Write 30min\n"
				"Pair Programming vs Noise 45min\n"
				"Rails Magic 60min\n"
				"Ruby on Rails: Why We Should Move On 60min\n"
				"Clojure Ate Scala (on my project) 45min\n"
				"Programming in the Boondocks of Seattle 30min\n"
				"Ruby vs. Clojure for Back-End Development 30min\n"
				"Ruby on Rails Legacy App Maintenance 60min\n"
				"A World Without HackerNews 30min\n"
				"User Interface CSS in Rails Apps 30min\n\n";

			// Test
			Assert::AreEqual(expected, buffer.str());
		}

		TEST_METHOD(TestCompareTimeOfDay)
		{
			TimeOfDay time1(12, 15, Period::PM);
			TimeOfDay time2(12, 15, Period::PM);
			TimeOfDay time3(10, 15, Period::AM);
			TimeOfDay time4(12, 5, Period::PM);
			TimeOfDay time5(1, 15, Period::PM);

			Assert::IsTrue(time1 == time2);
			Assert::IsTrue(time3 < time5);
			Assert::IsTrue(time3 <= time2);
			Assert::IsTrue(time1 <= time2);
			Assert::IsTrue(time3 != time2);
			Assert::IsTrue(time5 > time1);
			Assert::IsTrue(time2 >= time1);
			Assert::IsTrue(time1 >= time4);
		}

		TEST_METHOD(TestOutputOfSortedConference)
		{
			ConferenceManager conference{};
			conference.ReadInputFile(std::ifstream("..\\..\\talks.txt"));
			conference.SortTalksOnTracks();

			std::stringstream buffer;
			buffer << conference;

			std::string expected =
				"Track 1\n"
				"09:00AM Ruby on Rails Legacy App Maintenance 60min\n"
				"10:00AM Common Ruby Errors 45min\n"
				"10:45AM Sit Down and Write 30min\n"
				"11:15AM Programming in the Boondocks of Seattle 30min\n"
				"12:00PM Lunch\n"
				"01:00PM Writing Fast Tests Against Enterprise Rails 60min\n"
				"02:00PM Ruby on Rails: Why We Should Move On 60min\n"
				"03:00PM Accounting-Driven Development 45min\n"
				"03:45PM Woah 30min\n"
				"04:15PM Ruby vs. Clojure for Back-End Development 30min\n"
				"04:45PM Networking Event\n\n"
				"Track 2\n"
				"09:00AM Overdoing it in Python 45min\n"
				"09:45AM Ruby Errors from Mismatched Gem Versions 45min\n"
				"10:30AM Clojure Ate Scala (on my project) 45min\n"
				"11:15AM User Interface CSS in Rails Apps 30min\n"
				"11:45AM Rails for Python Developers lightning\n"
				"12:00PM Lunch\n"
				"01:00PM Communicating Over Distance 60min\n"
				"02:00PM Rails Magic 60min\n"
				"03:00PM Pair Programming vs Noise 45min\n"
				"03:45PM Lua for the Masses 30min\n"
				"04:15PM A World Without HackerNews 30min\n"
				"04:45PM Networking Event\n\n";

			// Test
			Assert::AreEqual(expected, buffer.str());
		}
	};
}
