#include "pch.h"
#include "CppUnitTest.h"
#include "Talk.h"

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
			Assert::AreEqual(60, task.GetLength());
		}
		TEST_METHOD(InitalizeLightningTalk)
		{
			std::string inputString = "Rails for Python Developers lightning";
			Talk task = Talk{inputString};
			Assert::AreEqual(std::string("Rails for Python Developers"), task.GetName());
			Assert::AreEqual(5, task.GetLength());
		}
	};
}
