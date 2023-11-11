#pragma once

#include <iostream>
#include <initializer_list>
#include <memory>
#include <cassert>	
#include "Vector.h"

namespace
{
#define CAST_TYPE(x) (static_cast<primitive_type>(x))
#define ZERO CAST_TYPE(0)
#define ONE CAST_TYPE(1)
}

namespace CKMath
{
	template<int matrix_row, int matrix_col, class primitive_type>
	struct Matrix
	{
	public:
		using Type = primitive_type;
		static constexpr int Row = matrix_row;
		static constexpr int Column = matrix_col;

	public:
		constexpr Matrix() noexcept
		{
			for (int i = 0; i < matrix_row; i++)
			{
				for (int j = 0; j < matrix_col; j++)
				{
					m_matrix[i][j] = ZERO;
				}
			}
		}

		constexpr Matrix(std::initializer_list<primitive_type> init_list) noexcept
			: Matrix()
		{
			assert(init_list.size() <= matrix_row * matrix_col);

			int i = 0;
			int j = 0;
			for (auto e : init_list)
			{
				m_matrix[i][j++] = e;

				if (j >= matrix_col)
				{
					j = 0;
					i++;
				}
			}
		}

	public:
		inline primitive_type* operator[](int i)
		{
			return m_matrix[i];
		}

		constexpr Matrix operator+(const Matrix<matrix_row, matrix_col, primitive_type>& rhs_m) const noexcept
		{
			Matrix<matrix_row, matrix_col, primitive_type> m;

			for (int i = 0; i < matrix_row; i++)
			{
				for (int j = 0; j < matrix_col; j++)
				{
					m[i][j] = this->GetAt(i, j) + rhs_m.GetAt(i, j);
				}
			}

			return m;
		}

		constexpr Matrix operator-(const Matrix<matrix_row, matrix_col, primitive_type>& rhs_m) const noexcept
		{
			Matrix<matrix_row, matrix_col, primitive_type> m;

			for (int i = 0; i < matrix_row; i++)
			{
				for (int j = 0; j < matrix_col; j++)
				{
					m[i][j] = this->GetAt(i, j) - rhs_m.GetAt(i, j);
				}
			}

			return m;
		}

		constexpr Matrix operator*(const primitive_type& value) const noexcept
		{
			Matrix<matrix_row, matrix_col, primitive_type> m;

			for (int i = 0; i < matrix_row; i++)
			{
				for (int j = 0; j < matrix_col; j++)
				{
					m[i][j] = this->GetAt(i, j) * value;
				}
			}

			return m;
		}
		constexpr Matrix operator/(const primitive_type& value) const noexcept
		{
			Matrix<matrix_row, matrix_col, primitive_type> m;

			primitive_type inverse_numver = 1.f / value;

			for (int i = 0; i < matrix_row; i++)
			{
				for (int j = 0; j < matrix_col; j++)
				{
					m[i][j] = this->GetAt(i, j) * inverse_numver;
				}
			}

			return m;
		}

		template<class TM, std::enable_if<TM::Row == matrix_col, int>::type = 0>
		constexpr Matrix<TM::Row, TM::Column, primitive_type> operator*(const TM& rhs_m) const noexcept
		{

			Matrix<TM::Row, TM::Column, primitive_type> m;

			assert(matrix_col == TM::Row);

			for (int j = 0; j < TM::Column; j++)
			{
				for (int i = 0; i < TM::Row; i++)
				{
					primitive_type value = ZERO;
					for (int other_i = 0; other_i < TM::Row; other_i++)
					{
						value += m_matrix[i][other_i] * rhs_m.GetAt(other_i, j);
					}

					m[i][j] = value;
				}
			}

			return m;
		}

	public:
		constexpr static inline Matrix<matrix_row, matrix_col, primitive_type> CreateIdentity() noexcept
		{
			Matrix<matrix_row, matrix_col, primitive_type> m;

			constexpr int min = matrix_row < matrix_col ? matrix_row : matrix_col;

			for (int i = 0; i < min; i++)
			{
				m.m_matrix[i][i] = ONE;
			}

			return m;
		}
		constexpr static inline Matrix<matrix_row, matrix_col, primitive_type> CreateZero() noexcept
		{
			return Matrix<matrix_row, matrix_col, primitive_type>();
		}

	public:
		constexpr inline void SetAt(int row, int col, primitive_type value) noexcept
		{
			AssertIndex(row, col);

			m_matrix[row][col] = value;
		}

		constexpr inline primitive_type GetAt(int row, int col) const noexcept
		{
			AssertIndex(row, col);

			return m_matrix[row][col];
		}

	private:
		constexpr inline void AssertIndex(const int& row, const int& col) const noexcept
		{
			assert(row >= 0 && row < matrix_row);
			assert(col >= 0 && col < matrix_col);
		}

	private:
		primitive_type m_matrix[matrix_row][matrix_col];
	};

	template<class primitive_type>
	struct Matrix<0, 0, primitive_type>
	{
	public:
		using Type = primitive_type;

	private:
		using TVector = _tagVector<primitive_type>;

	public:
		constexpr inline static Matrix<4, 4, primitive_type> CreateAMatrix4x4
		(const TVector& baseX, const TVector& baseY, const TVector& baseZ, const TVector& position = TVector::zero) noexcept
		{
			return Matrix<4, 4, primitive_type>
			{
				baseX.x, baseY.x, baseZ.x, position.x,
					baseX.y, baseY.y, baseZ.y, position.y,
					baseX.z, baseY.z, baseZ.z, position.z,
					CAST_TYPE(0), CAST_TYPE(0), CAST_TYPE(0), CAST_TYPE(1)
			};
		}

		constexpr inline static Matrix<4, 4, primitive_type> CreateAMatrix4x4(const TVector& position) noexcept
		{
			return Matrix<4, 4, primitive_type>
			{
				ONE, ZERO, ZERO, position.x,
					ZERO, ONE, ZERO, position.y,
					ZERO, ZERO, ZERO, position.z,
					ZERO, ZERO, ZERO, ZERO
			};
		}

		constexpr inline static Matrix<3, 3, primitive_type> CreateAMatrix2x2
		(const TVector& baseX, const TVector& baseY, const TVector& position = TVector::zero)
		{
			return Matrix<3, 3, primitive_type>
			{
				baseX.x, baseY.x, position.x,
					baseX.y, baseY.y, position.y,
					baseX.z, baseY.z, position.z,
					ZERO, ZERO, ONE
			};
		}
		constexpr inline static Matrix<3, 3, primitive_type> CreateAMatrix2X2(const TVector& position) noexcept
		{
			return Matrix<3, 3, primitive_type>
			{
				ONE, ZERO, position.x,
					ZERO, ONE, position.y,
					ZERO, ZERO, ONE,
			};
		}

		constexpr inline static Matrix<4, 1, primitive_type> To3DAMatrix(const TVector& v) noexcept
		{
			return Matrix<4, 1, primitive_type>{v.x, v.y, v.z, ONE};
		}
		constexpr inline static Matrix<3, 1, primitive_type> To2DAMatrix(const TVector& v) noexcept
		{
			return Matrix<3, 1, primitive_type>{v.x, v.y, ONE};
		}

		template<int matrix_row, int matrix_col, primitive_type>
		constexpr inline static Matrix<matrix_col, matrix_row, primitive_type> Transpose(const Matrix<matrix_row, matrix_col, primitive_type>& m) noexcept
		{
			Matrix<matrix_col, matrix_row, primitive_type> tm;

			for (int i = 0; i < matrix_row; i++)
			{
				for (int j = 0; j < matrix_col; j++)
				{
					tm[j][i] = m.GetAt(i, j);
				}
			}

			return tm;
		}
	};
}