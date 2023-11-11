#include "Transform.h"

Transform::Transform(__POINT__ x, __POINT__ y)
	: m_position(Vector(x, y)), m_scale(Vector::one), m_rotation(Vector::zero), m_size(Vector::one)
{
}

Vector Transform::GetPosition() const
{
	return m_position;
}

void Transform::SetPosition(const Vector& pos)
{
	m_position = pos;
}

Vector Transform::GetScale() const
{
	return m_scale;
}

void Transform::SetScale(const Vector& scale)
{
	m_scale = scale;
}

Vector Transform::GetSize() const
{
	return m_size;
}

void Transform::SetSize(const Vector& size)
{
	m_size = size;
}

Vector Transform::ScaledSize() const
{
	return Vector(m_size.x * m_scale.x, m_size.y * m_scale.y);
}

Vector Transform::GetRotation() const
{
	return m_rotation;
}

void Transform::SetRotation(const Vector& rotation)
{
	m_rotation = rotation;
}

void Transform::Move(const Vector& v)
{
	m_position += v;
}
