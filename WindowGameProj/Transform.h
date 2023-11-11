#pragma once
#include "type.h"

namespace
{
	using namespace CKMath;
	typedef float __POINT__;
}


class Transform
{
private:
	Vector m_position;
	Vector m_scale;
	Vector m_size;
	Vector m_rotation;

public:
	Transform(__POINT__ x = 0, __POINT__ y = 0);

	Vector  GetPosition()		 const;
	void    SetPosition(const Vector&);
		    
	Vector  GetScale()		 const;
	void    SetScale(const Vector&);

	Vector GetSize() const;
	void SetSize(const Vector&);

	Vector ScaledSize() const;
		    
	Vector  GetRotation()		 const;
	void    SetRotation(const Vector&);
		    
	void    Move(const Vector&)		  ;

};

