#pragma once

#include "Matrix.h"
#include "Vector.h"

using Int8 = __int8;
using Int16 = __int16;
using Int32 = __int32;
using Int64 = __int64;


namespace CKMath
{
	using MathPrimitiveType = float;

	typedef _tagVector<MathPrimitiveType> Vector;
	using IVector = _tagVector<Int32>;
	using DVector = _tagVector<double>;
	using FVector = _tagVector<float>;

	using Matrix4x4 = Matrix<4, 4, MathPrimitiveType>;
	using Matrix4x1 = Matrix<4, 1, MathPrimitiveType>;
	using Matrix3x3 = Matrix<3, 3, MathPrimitiveType>;
	using Matrix3x1 = Matrix<3, 1, MathPrimitiveType>;
}