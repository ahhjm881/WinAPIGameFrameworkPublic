#pragma once
#include <Windows.h>

struct UpdateInfo
{
	float deltaTime;
	HINSTANCE hInst;
};

struct RenderInfo
{
	HWND hWnd;
	HDC hdc;
	HINSTANCE hInst;
	POINT halfRect;
	POINT screenSize;
};

struct CollisionInfo
{
	class Collider* collider;
};
