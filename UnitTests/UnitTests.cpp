#include <iostream>
#include "pch.h"

#include "CppUnitTest.h"
#include "Talk.h"
#include "AdditionalTypes.h"


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
			Assert::AreEqual(std::string(inputString), talk.GetName());
			Assert::AreEqual(60, talk.GetDuration());
		}
		TEST_METHOD(InitalizeLightningTalk)
		{
			std::string inputString = "Rails for Python Developers lightning";
			Talk talk = Talk{inputString};
			Assert::AreEqual(std::string(inputString), talk.GetName());
			Assert::AreEqual(5, talk.GetDuration());
		}
	};

	TEST_CLASS(OutputTests)
	{
	public:
		TEST_METHOD(OutputTimeOfDayNoLeadingZerosAM)
		{
			std::string expected = "10:15AM";

			std::stringstream buffer;

			TimeOfDay time = TimeOfDay{ 10, 15, Period::AM };
			buffer << time;

			// Test
			Assert::AreEqual(expected, buffer.str());
		}
		TEST_METHOD(OutputTimeOfDayWithLeadingZerosPM)
		{
			std::string expected = "03:05PM";

			std::stringstream buffer;

			TimeOfDay time = TimeOfDay{ 3, 5, Period::PM };
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

			std::stringstream buffer;

			buffer << talk;

			// Test
			Assert::AreEqual(expected, buffer.str());
		}
	};

	TEST_CLASS(OperationTests)
	{
	public:
		TEST_METHOD(AddMinutesToTime)
		{
			std::string expected = "10:45AM";

			TimeOfDay time = TimeOfDay(10, 15, Period::AM);
			time = time.AddMinutes(30);

			std::stringstream buffer;
			buffer << time;

			// Test
			Assert::AreEqual(expected, buffer.str());
		}

		TEST_METHOD(AddMinutesToTimeChangeOfPeriod)
		{
			std::string expected = "12:15PM";

			TimeOfDay time = TimeOfDay(11, 45, Period::AM);
			time = time.AddMinutes(30);

			std::stringstream buffer;
			buffer << time;

			// Test
			Assert::AreEqual(expected, buffer.str());

			// Go from 12 to 01 PM
			time = time.AddMinutes(60);
			expected = "01:15PM";

			buffer.str("");
			buffer << time;

			Assert::AreEqual(expected, buffer.str());
		}
	};
}
