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
			Talk task = Talk{inputString};
			Assert::AreEqual(std::string("Writing Fast Tests Against Enterprise Rails"), task.GetName());
			Assert::AreEqual(60, task.GetDuration());
		}
		TEST_METHOD(InitalizeLightningTalk)
		{
			std::string inputString = "Rails for Python Developers lightning";
			Talk task = Talk{inputString};
			Assert::AreEqual(std::string("Rails for Python Developers"), task.GetName());
			Assert::AreEqual(5, task.GetDuration());
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
	};
}
