
#include "UnitTest.h"
#include "matrix.hpp"

using namespace UnitTest;
using namespace Dye;

class MatrixTest : public TestFixture<MatrixTest>
{
public:
	TEST_FIXTURE( MatrixTest )
	{
		TEST_CASE(TestConstructor);
		TEST_CASE(TestMemberFunc);
		TEST_CASE(TestOperator);
		TEST_CASE(TestOther);
	}

private:
	void TestConstructor()
	{
		float2x2 mat0;
		mat0 = float2x2::zero();
		float3x3 mat1 = float3x3::identity();
		float4x4 mat2 = float4x4::diag(1, 2, 3, 4);

		float data[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
		float4x4 mat3(data);

		float4 row0(1, 2, 3, 4);
		float4 row1(5, 6, 7, 8);
		float4 row2(9, 10, 11, 12);
		float4 row3(13, 14, 15, 16);
		float4x4 mat4(row0, row1, row2, row3);
	
		bool equal = true;
		for (auto it3 = mat3.begin(), it4 = mat4.begin(); it3 != mat3.end(); ++it3, ++it4)
		{
			if (*it3 != *it4) equal = false;
		}
		ASSERT(equal);
	}

	void TestMemberFunc()
	{
		float4x4 mat = float4x4::diag(1, 2, 3, 4);
		float4 row0 = mat[0];
		float4 col2 = mat.col(2);
		mat.set_col(0, col2);

		ASSERT_EQUALS(mat[2][0], 3);
	}

	void TestOperator()
	{
		float3x3 mat1 = float3x3::diag(1, 2, 3);
		float3x3 mat2(1, 2, 3, 4, 5, 6, 7, 8, 9);
		float3x3 mat3 = mat1 + mat2;
		float3x3 mat4 = mat1 - mat2;
		float3x3 mat5 = mat3 * mat4;
		float3x3 mat6 = mat5 * 2;
		float3x3 mat7 = mat5 / 2;
		mat7 *= 2;
		mat7 /= mat5;
		float3x3 mat8 = -mat7;

		ASSERT_EQUALS(mat8[1][1], -1);
	}

	void TestOther()
	{
		float4x4 mat1 = float4x4::diag(1, 2, 3, 4);
		float4x4 mat2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

		float4x4 mat3 = mul(mat1, mat2);
		float4x4 mat4 = trans(mat3);

		float4 vec1 = float4(1, -1, 1, -1);
		float4 vec2 = mul(mat1, vec1);
		float4 vec3 = mul(vec1, mat1);

		bool equal = true;
		for (int i=0; i!=4; ++i)
		{
			equal &= vec2[i] == vec3[i];
		}
		ASSERT(equal);
	}
};

REGISTER_FIXTURE(MatrixTest);
