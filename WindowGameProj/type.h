#pragma once
#include "Vector.h"
#include "Matrix.h"

using Int8 = __int8;
using Int16 = __int16;
using Int32 = __int32;
using Int64 = __int64;


namespace CKMath
{
	using MathPrimitiveType = float;

	typedef CKMath::_tagVector<MathPrimitiveType> Vector;
	using IVector = _tagVector<int>;
	using FVector = _tagVector<float>;
	using DVector = _tagVector<double>;

	using Matrix4x4 = Matrix<4, 4, MathPrimitiveType>;
	using Matrix4x1 = Matrix<4, 1, MathPrimitiveType>;
	using Matrix3x3 = Matrix<3, 3, MathPrimitiveType>;
	using Matrix3x1 = Matrix<3, 1, MathPrimitiveType>;
}