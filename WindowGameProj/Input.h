#pragma once
#include "Game.h"
#include <Windows.h>

typedef UINT_PTR KeyType;

enum class KeyCode
{
	/*move*/ W,A,S,D,
	/*func*/ Q,E,R,F,G
};

class Input
{
private:
	Input() {}

private:
	static char m_key[256];

	static char m_click[3];
	static Vector m_mousePosition;

public:
	static bool GetKeyDown(KeyType vk);
	static bool GetKeyUp(KeyType vk);
	static bool GetKey(KeyType vk);

	static bool GetMouseButtonDown(int mouse);
	static bool GetMouseButtonUp(int mouse);
	static bool GetMouseButton(int mouse);

	// ViewPort ÁÂÇ¥°è ÁÂÇ¥
	static Vector GetMousePosition();
	static Vector GetMousePosition(const RenderInfo& ri);

	static void SetKey(WPARAM wParam, LPARAM lParam, bool up);
	static void Update();

	static void SetMousePosition(LPARAM lParam);
	static void SetMouseInput(int mouse, bool up);
};

