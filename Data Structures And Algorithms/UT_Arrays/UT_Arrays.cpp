#include "pch.h"
#include "CppUnitTest.h"
#include "Array.h"
#include<array>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTArrays
{
	TEST_CLASS(UTArrays)
	{
	public:
		TEST_METHOD(MergeArrays)
		{
			Array<int> scores1 = { 5,2,6,10,15,25 };
			Array<int> scores2 = { 5,3,7,10,15,20 };

			//result
			Array<int> result;
			result.Merge(&scores1, &scores2);

			//correct result
			Array<int> correctResult = {8,2,3,6,7,10,15,20,25};
			Assert::IsTrue(correctResult == result);
		}

		TEST_METHOD(UnionArrays)
		{
			//scores1
			Array<int> scores1;
			scores1.Add(3);
			scores1.Add(4);
			scores1.Add(5);
			scores1.Add(6);
			scores1.Add(10);

			//scores2
			Array<int> scores2;
			scores2.Add(2);
			scores2.Add(4);
			scores2.Add(5);
			scores2.Add(7);
			scores2.Add(12);

			//scores3
			Array<int> scores3;
			scores3.Union(&scores1, &scores2);

			//correct result
			Array<int> correctResult;
			correctResult.Add(2);
			correctResult.Add(3);
			correctResult.Add(4);
			correctResult.Add(5);
			correctResult.Add(6);
			correctResult.Add(7);
			correctResult.Add(10);
			correctResult.Add(12);
			Assert::IsTrue(correctResult == scores3);
		}

		TEST_METHOD(IntersectionArrays)
		{
			//scores1
			Array<int> scores1;
			scores1.Add(3);
			scores1.Add(4);
			scores1.Add(5);
			scores1.Add(6);
			scores1.Add(10);

			//scores2
			Array<int> scores2;
			scores2.Add(2);
			scores2.Add(4);
			scores2.Add(5);
			scores2.Add(7);
			scores2.Add(12);

			//scores3
			Array<int> scores3;
			scores3.Intersection(&scores1, &scores2);

			//correct result
			Array<int> correctResult;
			correctResult.Add(4);
			correctResult.Add(5);
			Assert::IsTrue(correctResult == scores3);
		}


		TEST_METHOD(DifferenceArrays)
		{
			//scores1
			Array<int> scores1;
			scores1.Add(3);
			scores1.Add(4);
			scores1.Add(5);
			scores1.Add(6);
			scores1.Add(10);

			//scores2
			Array<int> scores2;
			scores2.Add(2);
			scores2.Add(4);
			scores2.Add(5);
			scores2.Add(7);
			scores2.Add(12);

			//scores3
			Array<int> scores3;
			scores3.Difference(&scores1, &scores2);

			//correct result
			Array<int> correctResult;
			correctResult.Add(3);
			correctResult.Add(6);
			correctResult.Add(10);
			Assert::IsTrue(correctResult == scores3);
		}
	};
}
