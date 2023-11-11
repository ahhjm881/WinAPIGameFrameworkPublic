#pragma once
#include "Transform.h"
#include <Windows.h>
#include "Info.h"

class Camera
{
private:
	Camera() {}

private:
	static Transform* m_transform;

public:
	static Transform* GetTransform() { return m_transform; }

	static IVector WorldToScreen(const Vector& v, const RenderInfo& info)
	{
		IVector t = m_transform->GetPosition();

		IVector r
		(
			(int)(v.x + ((Int32)info.halfRect.x) - t.x),
			(int)(-v.y + ((Int32)info.halfRect.y) - -t.y)
		);

		return r;
	}

	static IVector ScreenToWorld(const Vector& v, const RenderInfo& info)
	{
		IVector t = m_transform->GetPosition();

		IVector r
		(
			(int)(v.x - ((Int32)info.halfRect.x) + t.x),
			(int)(-v.y + ((Int32)info.halfRect.y) + t.y)
		);

		return r;
	}

	static IVector ViewPortToWorld(const Vector& v, const RenderInfo& info)
	{
		IVector t = m_transform->GetPosition();

		IVector r
		(
			(int)(v.x * info.screenSize.x),
			(int)(v.y * info.screenSize.y)
		);

		return ScreenToWorld(r, info);
	}
};

