
#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <memory.h>

#include "vector.hpp"
#include "common_helper.h"

namespace Dye
{
	template<typename Type> class matrix_2x2t;
	template<typename Type> class matrix_3x3t;
	template<typename Type> class matrix_4x4t;

	typedef matrix_2x2t<float> float2x2;
	typedef matrix_3x3t<float> float3x3;
	typedef matrix_4x4t<float> float4x4;

	template<typename Type>
	class matrix_2x2t
	{
	public:
		matrix_2x2t()
		{
		}

		matrix_2x2t(const Type &_00, const Type &_01,
					const Type &_10, const Type &_11)
			: m_row0(_00, _01)
			, m_row1(_10, _11)
		{
		}

		matrix_2x2t(const vector_2t<Type> &row0, 
					const vector_2t<Type> &row1)
			: m_row0(row0)
			, m_row1(row1)
		{
		}

		matrix_2x2t(const Type * elements)
		{
			memcpy((void *)&m_row0, (const void *)elements, sizeof(matrix_2x2t));
		}

	public:
		static matrix_2x2t zero()
		{
			return matrix_2x2t();
		}
		
		static matrix_2x2t diag(const Type &_00, const Type &_11)
		{
			return matrix_2x2t(_00,   0,
								 0, _11);
		}

		static matrix_2x2t identity()
		{
			return diag(1, 1);
		}

	public:
		DECLARE_CONVERSION_TO_POINTER(Type, &m_row0)
		DECLARE_SUBSCRIPT_OPERATOR(vector_2t<Type>, &m_row0)
		DECLARE_NATIVE_ITERATOR(Type, &m_row0, 2*2)

	public:
		vector_2t<Type> col(size_t i) const
		{
			return vector_2t<Type>(m_row0[i], m_row1[i]);
		}

		void set_col(size_t i, const vector_2t<Type> &col_vec)
		{
			m_row0[i] = col_vec[0];
			m_row1[i] = col_vec[1];
		}

	public:
		matrix_2x2t& operator += (const matrix_2x2t &rhs)
		{
			m_row0 += rhs.m_row0;
			m_row1 += rhs.m_row1;
			return *this;
		}

		matrix_2x2t& operator -= (const matrix_2x2t &rhs)
		{
			m_row0 -= rhs.m_row0;
			m_row1 -= rhs.m_row1;
			return *this;
		}

		matrix_2x2t& operator *= (const Type &scale)
		{
			m_row0 *= scale;
			m_row1 *= scale;
			return *this;
		}

		matrix_2x2t& operator /= (const Type &scale)
		{
			m_row0 /= scale;
			m_row1 /= scale;
			return *this;
		}

		matrix_2x2t& operator *= (const matrix_2x2t &rhs)
		{
			m_row0 *= rhs.m_row0;
			m_row1 *= rhs.m_row1;
			return *this;
		}

		matrix_2x2t& operator /= (const matrix_2x2t &rhs)
		{
			m_row0 /= rhs.m_row0;
			m_row1 /= rhs.m_row1;
			return *this;
		}

	private:
		vector_2t<Type> m_row0;
		vector_2t<Type> m_row1;
	};

	template<typename Type>
	class matrix_3x3t
	{
	public:
		matrix_3x3t()
		{
		}

		matrix_3x3t(const Type &_00, const Type &_01, const Type &_02,
					const Type &_10, const Type &_11, const Type &_12,
					const Type &_20, const Type &_21, const Type &_22)
			: m_row0(_00, _01, _02)
			, m_row1(_10, _11, _12)
			, m_row2(_20, _21, _22)
		{
		}

		matrix_3x3t(const vector_3t<Type> &row0, 
					const vector_3t<Type> &row1, 
					const vector_3t<Type> &row2)
			: m_row0(row0)
			, m_row1(row1)
			, m_row2(row2)
		{
		}

		matrix_3x3t(const Type * elements)
		{
			memcpy((void *)&m_row0, (const void *)elements, sizeof(matrix_3x3t));
		}

	public:
		static matrix_3x3t zero()
		{
			return matrix_3x3t();
		}

		static matrix_3x3t diag(const Type &_00, const Type &_11, const Type &_22)
		{
			return matrix_3x3t(_00,   0,   0,
								 0, _11,   0,
								 0,   0, _22);
		}

		static matrix_3x3t identity()
		{
			return diag(1, 1, 1);
		}

	public:
		DECLARE_CONVERSION_TO_POINTER(Type, &m_row0)
		DECLARE_SUBSCRIPT_OPERATOR(vector_3t<Type>, &m_row0)
		DECLARE_NATIVE_ITERATOR(Type, &m_row0, 3*3)

	public:
		vector_3t<Type> col(size_t i) const
		{
			return vector_3t<Type>(m_row0[i], m_row1[i], m_row2[i]);
		}

		void set_col(size_t i, const vector_3t<Type> &col_vec)
		{
			m_row0[i] = col_vec[0];
			m_row1[i] = col_vec[1];
			m_row2[i] = col_vec[2];
		}

	public:
		matrix_3x3t& operator += (const matrix_3x3t &rhs)
		{
			m_row0 += rhs.m_row0;
			m_row1 += rhs.m_row1;
			m_row2 += rhs.m_row2;
			return *this;
		}

		matrix_3x3t& operator -= (const matrix_3x3t &rhs)
		{
			m_row0 -= rhs.m_row0;
			m_row1 -= rhs.m_row1;
			m_row2 -= rhs.m_row2;
			return *this;
		}

		matrix_3x3t& operator *= (const Type &scale)
		{
			m_row0 *= scale;
			m_row1 *= scale;
			m_row2 *= scale;
			return *this;
		}

		matrix_3x3t& operator /= (const Type &scale)
		{
			m_row0 /= scale;
			m_row1 /= scale;
			m_row2 /= scale;
			return *this;
		}

		matrix_3x3t& operator *= (const matrix_3x3t &rhs)
		{
			m_row0 *= rhs.m_row0;
			m_row1 *= rhs.m_row1;
			m_row2 *= rhs.m_row2;
			return *this;
		}

		matrix_3x3t& operator /= (const matrix_3x3t &rhs)
		{
			m_row0 /= rhs.m_row0;
			m_row1 /= rhs.m_row1;
			m_row2 /= rhs.m_row2;
			return *this;
		}

	private:
		vector_3t<Type> m_row0;
		vector_3t<Type> m_row1;
		vector_3t<Type> m_row2;
	};

	template<typename Type>
	class matrix_4x4t
	{
	public:
		matrix_4x4t()
		{
		}

		matrix_4x4t(const Type &_00, const Type &_01, const Type &_02, const Type &_03,
					const Type &_10, const Type &_11, const Type &_12, const Type &_13,
					const Type &_20, const Type &_21, const Type &_22, const Type &_23,
					const Type &_30, const Type &_31, const Type &_32, const Type &_33)
			: m_row0(_00, _01, _02, _03)
			, m_row1(_10, _11, _12, _13)
			, m_row2(_20, _21, _22, _23)
			, m_row3(_30, _31, _32, _33)
		{
		}

		matrix_4x4t(const vector_4t<Type> &row0, 
					const vector_4t<Type> &row1, 
					const vector_4t<Type> &row2,
					const vector_4t<Type> &row3)
			: m_row0(row0)
			, m_row1(row1)
			, m_row2(row2)
			, m_row3(row3)
		{
		}

		matrix_4x4t(const Type * elements)
		{
			memcpy((void *)&m_row0, (const void *)elements, sizeof(matrix_4x4t));
		}

	public:
		static matrix_4x4t zero()
		{
			return matrix_4x4t();
		}

		static matrix_4x4t diag(const Type &_00, const Type &_11, const Type &_22, const Type &_33)
		{
			return matrix_4x4t(_00,   0,   0,   0,
								 0, _11,   0,   0,
								 0,   0, _22,   0,
								 0,   0,   0, _33);
		}

		static matrix_4x4t identity()
		{
			return diag(1, 1, 1, 1);
		}

	public:
		DECLARE_CONVERSION_TO_POINTER(Type, &m_row0)
		DECLARE_SUBSCRIPT_OPERATOR(vector_4t<Type>, &m_row0)
		DECLARE_NATIVE_ITERATOR(Type, &m_row0, 4*4)

	public:
		vector_4t<Type> col(size_t i) const
		{
			return vector_4t<Type>(m_row0[i], m_row1[i], m_row2[i], m_row3[i]);
		}

		void set_col(size_t i, const vector_4t<Type> &col_vec)
		{
			m_row0[i] = col_vec[0];
			m_row1[i] = col_vec[1];
			m_row2[i] = col_vec[2];
			m_row3[i] = col_vec[3];
		}

	public:
		matrix_4x4t& operator += (const matrix_4x4t &rhs)
		{
			m_row0 += rhs.m_row0;
			m_row1 += rhs.m_row1;
			m_row2 += rhs.m_row2;
			m_row3 += rhs.m_row3;
			return *this;
		}

		matrix_4x4t& operator -= (const matrix_4x4t &rhs)
		{
			m_row0 -= rhs.m_row0;
			m_row1 -= rhs.m_row1;
			m_row2 -= rhs.m_row2;
			m_row3 -= rhs.m_row3;
			return *this;
		}

		matrix_4x4t& operator *= (const Type &scale)
		{
			m_row0 *= scale;
			m_row1 *= scale;
			m_row2 *= scale;
			m_row3 *= scale;
			return *this;
		}

		matrix_4x4t& operator /= (const Type &scale)
		{
			m_row0 /= scale;
			m_row1 /= scale;
			m_row2 /= scale;
			m_row3 /= scale;
			return *this;
		}

		matrix_4x4t& operator *= (const matrix_4x4t &rhs)
		{
			m_row0 *= rhs.m_row0;
			m_row1 *= rhs.m_row1;
			m_row2 *= rhs.m_row2;
			m_row3 *= rhs.m_row3;
			return *this;
		}

		matrix_4x4t& operator /= (const matrix_4x4t &rhs)
		{
			m_row0 /= rhs.m_row0;
			m_row1 /= rhs.m_row1;
			m_row2 /= rhs.m_row2;
			m_row3 /= rhs.m_row3;
			return *this;
		}

	private:
		vector_4t<Type> m_row0;
		vector_4t<Type> m_row1;
		vector_4t<Type> m_row2;
		vector_4t<Type> m_row3;
	};

	//////////////////////////////////////////////////////////////////////////
	// negation
	template<typename Type>
	matrix_2x2t<Type> operator - (const matrix_2x2t<Type> &operand)
	{
		return matrix_2x2t<Type>(-operand[0], -operand[1]);
	}

	template<typename Type>
	matrix_3x3t<Type> operator - (const matrix_3x3t<Type> &operand)
	{
		return matrix_3x3t<Type>(-operand[0], -operand[1], -operand[2]);
	}

	template<typename Type>
	matrix_4x4t<Type> operator - (const matrix_4x4t<Type> &operand)
	{
		return matrix_4x4t<Type>(-operand[0], -operand[1], -operand[2], -operand[3]);
	}

	//////////////////////////////////////////////////////////////////////////
	// addition
	template<typename Type>
	matrix_2x2t<Type> operator + (const matrix_2x2t<Type> &lhs, const matrix_2x2t<Type> &rhs)
	{
		return matrix_2x2t<Type> (lhs[0] + rhs[0], lhs[1] + rhs[1]);
	}

	template<typename Type>
	matrix_3x3t<Type> operator + (const matrix_3x3t<Type> &lhs, const matrix_3x3t<Type> &rhs)
	{
		return matrix_3x3t<Type> (lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
	}

	template<typename Type>
	matrix_4x4t<Type> operator + (const matrix_4x4t<Type> &lhs, const matrix_4x4t<Type> &rhs)
	{
		return matrix_4x4t<Type> (lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2], lhs[3] + rhs[3]);
	}

	//////////////////////////////////////////////////////////////////////////
	// subtraction
	template<typename Type>
	matrix_2x2t<Type> operator - (const matrix_2x2t<Type> &lhs, const matrix_2x2t<Type> &rhs)
	{
		return matrix_2x2t<Type> (lhs[0] - rhs[0], lhs[1] - rhs[1]);
	}

	template<typename Type>
	matrix_3x3t<Type> operator - (const matrix_3x3t<Type> &lhs, const matrix_3x3t<Type> &rhs)
	{
		return matrix_3x3t<Type> (lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]);
	}

	template<typename Type>
	matrix_4x4t<Type> operator - (const matrix_4x4t<Type> &lhs, const matrix_4x4t<Type> &rhs)
	{
		return matrix_4x4t<Type> (lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2], lhs[3] - rhs[3]);
	}

	//////////////////////////////////////////////////////////////////////////
	// multiplication : matrix * scalar
	template<typename Type, typename S>
	matrix_2x2t<Type> operator * (const matrix_2x2t<Type> &lhs, const S& scale)
	{
		return matrix_2x2t<Type> (lhs[0] * scale, lhs[1] * scale);
	}

	template<typename Type, typename S>
	matrix_3x3t<Type> operator * (const matrix_3x3t<Type> &lhs, const S& scale)
	{
		return matrix_3x3t<Type> (lhs[0] * scale, lhs[1] * scale, lhs[2] * scale);
	}

	template<typename Type, typename S>
	matrix_4x4t<Type> operator * (const matrix_4x4t<Type> &lhs, const S& scale)
	{
		return matrix_4x4t<Type> (lhs[0] * scale, lhs[1] * scale, lhs[2] * scale, lhs[3] * scale);
	}

	//////////////////////////////////////////////////////////////////////////
	// multiplication : scalar * matrix
	template<typename Type, typename S>
	matrix_2x2t<Type> operator * (const S& scale , const matrix_2x2t<Type> &rhs)
	{
		return matrix_2x2t<Type> (rhs[0] * scale, rhs[1] * scale);
	}

	template<typename Type, typename S>
	matrix_3x3t<Type> operator * (const S& scale , const matrix_3x3t<Type> &rhs)
	{
		return matrix_3x3t<Type> (rhs[0] * scale, rhs[1] * scale, rhs[2] * scale);
	}

	template<typename Type, typename S>
	matrix_4x4t<Type> operator * (const S& scale , const matrix_4x4t<Type> &rhs)
	{
		return matrix_4x4t<Type> (rhs[0] * scale, rhs[1] * scale, rhs[2] * scale, rhs[3] * scale);
	}

	//////////////////////////////////////////////////////////////////////////
	// division : matrix / scalar
	template<typename Type, typename S>
	matrix_2x2t<Type> operator / (const matrix_2x2t<Type> &lhs, const S& scale)
	{
		return matrix_2x2t<Type> (lhs[0] / scale, lhs[1] / scale);
	}

	template<typename Type, typename S>
	matrix_3x3t<Type> operator / (const matrix_3x3t<Type> &lhs, const S& scale)
	{
		return matrix_3x3t<Type> (lhs[0] / scale, lhs[1] / scale, lhs[2] / scale);
	}

	template<typename Type, typename S>
	matrix_4x4t<Type> operator / (const matrix_4x4t<Type> &lhs, const S& scale)
	{
		return matrix_4x4t<Type> (lhs[0] / scale, lhs[1] / scale, lhs[2] / scale, lhs[3] / scale);
	}

	//////////////////////////////////////////////////////////////////////////
	// piecewise multiplication : matrix * matrix
	template<typename Type>
	matrix_2x2t<Type> operator * (const matrix_2x2t<Type> &lhs, const matrix_2x2t<Type> &rhs)
	{
		return matrix_2x2t<Type> (lhs[0] * rhs[0], lhs[1] * rhs[1]);
	}

	template<typename Type>
	matrix_3x3t<Type> operator * (const matrix_3x3t<Type> &lhs, const matrix_3x3t<Type> &rhs)
	{
		return matrix_3x3t<Type> (lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]);
	}

	template<typename Type>
	matrix_4x4t<Type> operator * (const matrix_4x4t<Type> &lhs, const matrix_4x4t<Type> &rhs)
	{
		return matrix_4x4t<Type> (lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2], lhs[3] * rhs[3]);
	}

	//////////////////////////////////////////////////////////////////////////
	// piecewise division : matrix / matrix
	template<typename Type>
	matrix_2x2t<Type> operator / (const matrix_2x2t<Type> &lhs, const matrix_2x2t<Type> &rhs)
	{
		return matrix_2x2t<Type> (lhs[0] / rhs[0], lhs[1] / rhs[1]);
	}

	template<typename Type>
	matrix_3x3t<Type> operator / (const matrix_3x3t<Type> &lhs, const matrix_3x3t<Type> &rhs)
	{
		return matrix_3x3t<Type> (lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2]);
	}

	template<typename Type>
	matrix_4x4t<Type> operator / (const matrix_4x4t<Type> &lhs, const matrix_4x4t<Type> &rhs)
	{
		return matrix_4x4t<Type> (lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2], lhs[3] / rhs[3]);
	}

	//////////////////////////////////////////////////////////////////////////
	// transposition
	template<typename Type>
	matrix_2x2t<Type> trans(const matrix_2x2t<Type> &operand)
	{
		return matrix_2x2t<Type> (operand.col(0), operand.col(1));
	}

	template<typename Type>
	matrix_3x3t<Type> trans(const matrix_3x3t<Type> &operand)
	{
		return matrix_3x3t<Type> (operand.col(0), operand.col(1), operand.col(2));
	}

	template<typename Type>
	matrix_4x4t<Type> trans(const matrix_4x4t<Type> &operand)
	{
		return matrix_4x4t<Type> (operand.col(0), operand.col(1), operand.col(2), operand.col(3));
	}

	//////////////////////////////////////////////////////////////////////////
	// matrix multiplication : mul(row vector, matrix)
	template<typename Type>
	vector_2t<Type> mul (const vector_2t<Type> &lhs, const matrix_2x2t<Type> &rhs)
	{
		return vector_2t<Type> (dot(lhs, rhs.col(0)), dot(lhs, rhs.col(1)));
	}

	template<typename Type>
	vector_3t<Type> mul (const vector_3t<Type> &lhs, const matrix_3x3t<Type> &rhs)
	{
		return vector_3t<Type> (dot(lhs, rhs.col(0)), dot(lhs, rhs.col(1)), dot(lhs, rhs.col(2)));
	}

	template<typename Type>
	vector_4t<Type> mul (const vector_4t<Type> &lhs, const matrix_4x4t<Type> &rhs)
	{
		return vector_4t<Type> (dot(lhs, rhs.col(0)), dot(lhs, rhs.col(1)), dot(lhs, rhs.col(2)), dot(lhs, rhs.col(3)));
	}

	//////////////////////////////////////////////////////////////////////////
	// matrix multiplication : mul(matrix, col vector)
	template<typename Type>
	vector_2t<Type> mul (const matrix_2x2t<Type> &lhs, const vector_2t<Type> &rhs)
	{
		return vector_2t<Type> (dot(lhs[0], rhs), dot(lhs[1], rhs));
	}

	template<typename Type>
	vector_3t<Type> mul (const matrix_3x3t<Type> &lhs, const vector_3t<Type> &rhs)
	{
		return vector_3t<Type> (dot(lhs[0], rhs), dot(lhs[1], rhs), dot(lhs[2], rhs));
	}

	template<typename Type>
	vector_4t<Type> mul (const matrix_4x4t<Type> &lhs, const vector_4t<Type> &rhs)
	{
		return vector_4t<Type> (dot(lhs[0], rhs), dot(lhs[1], rhs), dot(lhs[2], rhs), dot(lhs[3], rhs));
	}

	//////////////////////////////////////////////////////////////////////////
	// matrix multiplication : mul(matrix, matrix)
	template<typename Type>
	matrix_2x2t<Type> mul (const matrix_2x2t<Type> &lhs, const matrix_2x2t<Type> &rhs)
	{
		vector_2t<Type> rhs_col0 = rhs.col(0);
		vector_2t<Type> rhs_col1 = rhs.col(1);
		
		return matrix_2x2t<Type> (
			dot(lhs[0], rhs_col0), dot(lhs[0], rhs_col1),
			dot(lhs[1], rhs_col0), dot(lhs[1], rhs_col1));
	}

	template<typename Type>
	matrix_3x3t<Type> mul (const matrix_3x3t<Type> &lhs, const matrix_3x3t<Type> &rhs)
	{
		vector_3t<Type> rhs_col0 = rhs.col(0);
		vector_3t<Type> rhs_col1 = rhs.col(1);
		vector_3t<Type> rhs_col2 = rhs.col(2);
		
		return matrix_3x3t<Type> (
			dot(lhs[0], rhs_col0), dot(lhs[0], rhs_col1), dot(lhs[0], rhs_col2),
			dot(lhs[1], rhs_col0), dot(lhs[1], rhs_col1), dot(lhs[1], rhs_col2),
			dot(lhs[2], rhs_col0), dot(lhs[2], rhs_col1), dot(lhs[2], rhs_col2));
	}

	template<typename Type>
	matrix_4x4t<Type> mul (const matrix_4x4t<Type> &lhs, const matrix_4x4t<Type> &rhs)
	{
		vector_4t<Type> rhs_col0 = rhs.col(0);
		vector_4t<Type> rhs_col1 = rhs.col(1);
		vector_4t<Type> rhs_col2 = rhs.col(2);
		vector_4t<Type> rhs_col3 = rhs.col(3);
		
		return matrix_4x4t<Type> (
			dot(lhs[0], rhs_col0), dot(lhs[0], rhs_col1), dot(lhs[0], rhs_col2), dot(lhs[0], rhs_col3),
			dot(lhs[1], rhs_col0), dot(lhs[1], rhs_col1), dot(lhs[1], rhs_col2), dot(lhs[1], rhs_col3),
			dot(lhs[2], rhs_col0), dot(lhs[2], rhs_col1), dot(lhs[2], rhs_col2), dot(lhs[2], rhs_col3),
			dot(lhs[3], rhs_col0), dot(lhs[3], rhs_col1), dot(lhs[3], rhs_col2), dot(lhs[3], rhs_col3));
	}
}

#endif // _MATRIX_HPP_