#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab12_3.2A\main.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Student* s = new Student[1];
			s[0] = { "Бандера", 2, Spec::KN, 3, 3, 3 };
			Assert::AreEqual(avgMark(*s), 3.);
			delete[] s;
		}
	};
}
