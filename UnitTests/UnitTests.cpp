#include <iostream>
#include "pch.h"
#include "CppUnitTest.h"

#include "AdditionalTypes.h"
#include "Talk.h"
#include "Session.h"
#include "Track.h"


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

			Session session2 = track.GetAfternoonSession();

			// Adding three talks to the session
			std::string inputString = "Ruby Errors from Mismatched Gem Versions 45min";
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
				"12:00PM Lunch"
				"01:00PM Ruby Errors from Mismatched Gem Versions 45min"
				"01:45PM Common Ruby Errors 45min"
				"02:30PM Rails for Python Developers lightning"
				"04:00PM Networking Event";

			// Output session
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
	};
}
