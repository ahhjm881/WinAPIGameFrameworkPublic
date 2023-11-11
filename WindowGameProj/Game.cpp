#include "Game.h"
#include "Camera.h"
#include "TestScene.h"


HINSTANCE Game::m_hInst = 0;

Game::Game(HINSTANCE hInst)
	: m_currentScene(nullptr)
{

	Debug::Initialize();
	m_hInst = hInst;

	m_currentScene = new TestScene();

}


void Game::Loop(float deltaTime, HWND hWnd, HDC hdc)
{
	RECT r;
	GetClientRect(hWnd, &r);
	HDC hMemdc = CreateCompatibleDC(hdc); // 화면dc(그릴 윈도우) 기반 메모리 DC생성 
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, r.right, r.bottom); // 비트맵 생성
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemdc, hBitmap); // 비트맵 선택


	RenderInfo ri{ hWnd, hMemdc, m_hInst, {(LONG)((double)r.right * 0.5), (LONG)((double)r.bottom * 0.5)}, {r.right, r.bottom} };
	UpdateInfo ui{ deltaTime, m_hInst };

	m_currentScene->Loop(ui, ri);
	Debug::Render(ri);

	BitBlt(hdc, 0, 0, r.right, r.bottom, hMemdc, 0, 0, SRCCOPY); // 고속복사 hMemdc->hdc
	SelectObject(hMemdc, hOldBitmap); // 기존 비트맵 선택
	ReleaseDC(hWnd, hMemdc); // 메모리 dc 해제
	DeleteObject(hOldBitmap);
	DeleteObject(hBitmap);

	Input::Update();
}

HINSTANCE Game::GethInstance()
{
	return m_hInst;
}