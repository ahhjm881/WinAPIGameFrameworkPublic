#pragma once

#include <cmath>

namespace CKMath
{
	template<typename T>
	struct _tagVector
	{
	public:
		T x;
		T y;
		T z;

		using Type = T;

	public:
		constexpr _tagVector() noexcept
			: x((T)0), y((T)0), z((T)0) {}

		constexpr _tagVector(T _x, T _y) noexcept
			: x((T)_x), y((T)_y), z((T)0) {}

		constexpr _tagVector(T _x, T _y, T _z) noexcept
			: x((T)_x), y((T)_y), z((T)_z) {}

		__forceinline constexpr _tagVector<T> operator+(const _tagVector<T>& v1) const noexcept
		{
			return _tagVector<T>(v1.x + x, v1.y + y, v1.z + z);
		}

		__forceinline constexpr _tagVector<T> operator-(const _tagVector<T>& v1) const noexcept
		{
			return _tagVector<T>(x - v1.x, y - v1.y, z - v1.z);
		}

		template<class U>
		__forceinline constexpr _tagVector<T> operator*(const U& value) const noexcept
		{
			return _tagVector<T>((T)(x * value), (T)(y * value), (T)(y * value));
		}

		template<class U>
		__forceinline constexpr _tagVector<T> operator/(const U& value) const noexcept
		{
			return _tagVector<T>((T)(x / value), (T)(y / value), (T)(z / value));
		}

		__forceinline constexpr void operator+=(const _tagVector<T>& v1) noexcept
		{
			x += v1.x;
			y += v1.y;
			z += v1.z;
		}
		__forceinline constexpr void operator-=(const _tagVector<T>& v1) noexcept
		{
			x -= v1.x;
			y -= v1.y;
			z -= v1.z;
		}

		__forceinline constexpr bool operator==(const _tagVector<T>& v) const noexcept
		{
			return (v.x == x && v.y == y && v.z == z);
		}

		template<class U>
		__forceinline constexpr void operator*=(const U& value) noexcept
		{
			x *= value;
			y *= value;
			z *= value;
		}

		template<class U>
		__forceinline constexpr void operator/=(const U& value) noexcept
		{
			x /= value;
			y /= value;
			z /= value;
		}

		__forceinline constexpr _tagVector<T> operator-(void) const noexcept
		{
			return _tagVector<T>(-x, -y, -z);
		}

		template<typename U>
		__forceinline constexpr operator _tagVector<U>() const noexcept
		{
			return _tagVector<U>((U)x, (U)y, (U)z);
		}

		__forceinline constexpr T Magnitude() const noexcept
		{
			return sqrt(x * x + y * y + z * z);
		}

		__forceinline constexpr T sqrMagnitude() const noexcept
		{
			return x * x + y * y + z * z;
		}

		__forceinline static constexpr _tagVector<T> Lerp(const _tagVector<T>& from, const _tagVector<T>& to, float t)  noexcept
		{
			if (t < 0.f)t = 0.f;
			if (t > 1.f) t = 1.f;

			float s = t - 1;

			return (s * from) + (t * to);
		}

		__forceinline static constexpr _tagVector<T> MoveToWord(const _tagVector<T>& from, const _tagVector<T>& to, float speed) noexcept
		{
			_tagVector<T> v = (to - from);

			if (v.sqrMagnitude() <= FLT_EPSILON)
			{
				return to;
			}

			_tagVector<T> dir = v.Normalize();

			_tagVector<T> movedV = dir * speed;
			_tagVector<T> movedPos;

			if (movedV.sqrMagnitude() > v.sqrMagnitude())
			{
				movedPos = to;
			}
			else
			{
				movedPos = from + movedV;
			}

			return movedPos;

		}

		__forceinline constexpr _tagVector<T> Normalize() const noexcept
		{
			T m = Magnitude();
			return _tagVector<T>(x / m, y / m);
		}

		template<typename U>
		__forceinline static constexpr _tagVector<T> MultipleVector(_tagVector<T> v1, _tagVector<U> v2) noexcept
		{
			return _tagVector<T>((T)(v1.x * v2.x), (T)(v1.y * v2.y));
		}

		__forceinline static constexpr T Distance(_tagVector<T> v1, _tagVector<T> v2) noexcept
		{
			return (v1 - v2).Magnitude();
		}
		__forceinline constexpr T Dot(const _tagVector<T>& v1, const _tagVector<T>& v2) noexcept
		{
			return v1.x * v2.x + v1.y * v2.y;
		}
		__forceinline static constexpr _tagVector<T> Project(_tagVector<T> v, _tagVector<T> normal) noexcept
		{
			return normal * (_tagVector<T>::Dot(v, normal));
		}

	public:
		const static _tagVector<T> zero;
		const static _tagVector<T> one;
		const static _tagVector<T> right;
		const static _tagVector<T> left;
		const static _tagVector<T> up;
		const static _tagVector<T> down;
	};

	template<typename T> const _tagVector<T> _tagVector<T>::zero((T)0, (T)0);
	template<typename T> const _tagVector<T> _tagVector<T>::one((T)1, (T)1);
	template<typename T> const _tagVector<T> _tagVector<T>::right((T)1, (T)0);
	template<typename T> const _tagVector<T> _tagVector<T>::left((T)-1, (T)0);
	template<typename T> const _tagVector<T> _tagVector<T>::up((T)0, (T)1);
	template<typename T> const _tagVector<T> _tagVector<T>::down((T)0, (T)-1);

}