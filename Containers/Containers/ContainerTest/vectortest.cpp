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
			Vector<int> myv({ 1,2,3,4 });

			Assert::AreEqual((int)myv.size(), 4);

			myv.push_back(1);

			Assert::AreEqual(static_cast<int>(myv.size()), 5);
			// TODO: Your test code here
		}

	};
}