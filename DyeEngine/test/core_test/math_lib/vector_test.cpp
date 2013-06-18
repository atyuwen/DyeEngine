
#include "UnitTest.h"
#include "vector.hpp"

using namespace UnitTest;
using namespace Dye;

class VectorTest : public TestFixture<VectorTest>
{
public:
	TEST_FIXTURE( VectorTest )
	{
		TEST_CASE(TestIterator);
		TEST_CASE(TestOperator);
		TEST_CASE(TestDotProduct);
		TEST_CASE(TestCrossProduct);
		TEST_CASE(TestPiecewiseProduct);
		TEST_CASE(TestSwizzle);
		TEST_CASE(TestGeneral);
	}

private:
	void TestIterator()
	{
		float4 vec(1, 2, 3, 4);

		float sum = 0;
		for (float4::const_iterator it = vec.begin(); it != vec.end(); ++it)
		{
			sum += *it;
		}

		ASSERT_EQUALS(sum, 10);
	}

	void TestOperator()
	{
		float2 vec(1, 1);
		vec *= 2;
		vec += float2(3, 3);
		vec -= float2(1, 2);

		ASSERT_EQUALS(vec.length(), 5);
	}

	void TestDotProduct()
	{
		float2 vec1(1, 0);
		float2 vec2(0, 1);

		ASSERT_EQUALS(dot(vec1, vec1), 1);
		ASSERT_EQUALS(dot(vec1, vec2), 0);
	}

	void TestCrossProduct()
	{
		float2 vec1(1, 0);
		float2 vec2(0, 1);

		ASSERT_EQUALS(cross(vec1, vec1), 0);
		ASSERT_EQUALS(cross(vec1, vec2), 1);
	}

	void TestPiecewiseProduct()
	{
		float4 vec1(1, 1, 1, 1);
		float4 vec2(2, 2, 2, 2);

		float4 vec3 = vec1 * vec2;

		float sum = 0;
		for (auto it = vec3.begin(); it != vec3.end(); ++it)
		{
			sum += *it;
		}
		ASSERT_EQUALS(sum, 8);
	}

	void TestSwizzle()
	{
		float4 vec1(1, 2, 3, 4);

		float4 vec2 = vec1.wzyx();
		ASSERT_EQUALS(vec2.x, 4);
		ASSERT_EQUALS(vec2.y, 3);
		ASSERT_EQUALS(vec2.z, 2);
		ASSERT_EQUALS(vec2.w, 1);

		float3 vec3 = vec1.xxy();
		ASSERT_EQUALS(vec3.x, 1);
		ASSERT_EQUALS(vec3.y, 1);
		ASSERT_EQUALS(vec3.z, 2);
	}

	void TestGeneral()
	{
		float3 vec1(1, 2, 3);
		vec1 *= 2;
		float3 vec2 = 2 * vec1;
		float3 vec3 = vec1 * vec2;
		float3 vec4 = vec2 * vec3;
		float3 vec5 = vec4 / vec1;

		vec5 *= 2;
		float3 vec6 = vec5 / 2;

		float3 vec7 = vec1 - vec2;
		float3 vec8 = vec1 / vec2;
		float3 vec9 = vec1.xyz() / vec2.xxx();
	}
};

REGISTER_FIXTURE(VectorTest);