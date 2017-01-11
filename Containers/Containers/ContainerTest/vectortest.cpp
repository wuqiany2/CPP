#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ContainerTest
{		
	TEST_CLASS(VectorTest)
	{
	public:
		
		TEST_METHOD(SampleTest)
		{
			Vector<int> myv;

			Assert::AreEqual((int)myv.size(), 0);

			myv.push_back(1);

			Assert::AreEqual(static_cast<int>(myv.size()), 1);
			// TODO: Your test code here
		}

	};
}