#include "Input.h"

char Input::m_key[256]{ 0 };
char Input::m_click[]{ 0 };
Vector Input::m_mousePosition;

#define __INPUT__NO__ 0x0
#define __INPUT_DOWN__ 0x1
#define __INPUT_KEY__ 0x2
#define __INPUT_UP__ 0x3

bool Input::GetKeyDown(KeyType vk)
{
	return m_key[vk] == __INPUT_DOWN__;
}

bool Input::GetKeyUp(KeyType vk)
{
	return m_key[vk] == __INPUT_UP__;
}

bool Input::GetKey(KeyType vk)
{
	return m_key[vk] != __INPUT__NO__;
}

bool Input::GetMouseButtonDown(int mouse)
{
	if (mouse < 0 || mouse >= sizeof(m_click)) throw std::exception("mouse button id error");

	return m_click[mouse] == __INPUT_DOWN__;
}

bool Input::GetMouseButtonUp(int mouse)
{
	if (mouse < 0 || mouse >= sizeof(m_click)) throw std::exception("mouse button id error");

	return m_click[mouse] == __INPUT_UP__;
}

bool Input::GetMouseButton(int mouse)
{
	if (mouse < 0 || mouse >= sizeof(m_click)) throw std::exception("mouse button id error");

	return ((m_click[mouse] == __INPUT_DOWN__) || (m_click[mouse] == __INPUT_KEY__));
}

#include "Camera.h"
Vector Input::GetMousePosition(const RenderInfo& ri)
{
	return Camera::ScreenToWorld(m_mousePosition, ri);
}
Vector Input::GetMousePosition()
{
	return m_mousePosition;
}


void Input::SetMousePosition(LPARAM lParam)
{
	m_mousePosition.y = HIWORD(lParam);
	m_mousePosition.x = LOWORD(lParam);
}
#include "Debug.h"
void Input::SetMouseInput(int mouse, bool up)
{
	if (mouse < 0 || mouse >= sizeof(m_click)) throw std::exception("mouse button id error");

	m_click[mouse] = up ? __INPUT_UP__ : __INPUT_DOWN__;
}
void Input::Update()
{
	for (int i = 0; i < sizeof(m_key); i++)
	{
		switch (m_key[i])
		{
		case __INPUT_DOWN__:
			m_key[i] = __INPUT_KEY__;
			break;
		case __INPUT_UP__:
			m_key[i] = __INPUT__NO__;
			break;
		case __INPUT_KEY__:
			break;
		default:
			m_key[i] = __INPUT__NO__;
			break;
		}
	}

	for (int i = 0; i < sizeof(m_click); i++)
	{
		switch (m_click[i])
		{
		case __INPUT_DOWN__:
			m_click[i] = __INPUT_KEY__;
			break;
		case __INPUT_UP__:
			m_click[i] = __INPUT__NO__;
			break;
		case __INPUT_KEY__:
			break;
		default:
			m_click[i] = __INPUT__NO__;
			break;
		}
	}
}

void Input::SetKey(WPARAM wParam, LPARAM lParam, bool up)
{
	if (!up && (HIWORD(lParam) & KF_REPEAT) == KF_REPEAT)
		return;

	m_key[wParam] = up ? 0x3 : 1;
}