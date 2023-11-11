#pragma once
#include <Windows.h>
#include "Actor.h"
#include "Input.h"
#include "Info.h"
#include "Scene.h"

class Game
{
private:
	static HINSTANCE m_hInst;

private:
	Scene* m_currentScene;

public:
	Game(HINSTANCE hInst);

	void Loop(float, HWND, HDC);


public:
	static HINSTANCE GethInstance();
};