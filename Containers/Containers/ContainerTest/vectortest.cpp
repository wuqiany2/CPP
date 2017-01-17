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

			auto top = myv.pop_back();

			Assert::AreEqual(top, 1);

			Assert::AreEqual(static_cast<int>(myv.size()), 4);

			myv.push_back(5);

			Assert::AreEqual(static_cast<int>(myv.size()), 5);

			for (size_t i = 0; i < myv.size(); i++) {
				Assert::AreEqual(myv[i], static_cast<int>(i + 1));
			}

			myv[4] = 0;

			Assert::AreEqual(myv[4], 0);

			Assert::AreEqual(myv.back(), 0);
			
			myv.back() = 3;

			Assert::AreEqual(myv.back(), 3);

			Assert::ExpectException<std::out_of_range>([&]() {return myv[10]; });

			Vector<int> zero;

			Assert::ExpectException<std::out_of_range>([&]() {return zero.back(); });
			// TODO: Your test code here
		}

	};
}