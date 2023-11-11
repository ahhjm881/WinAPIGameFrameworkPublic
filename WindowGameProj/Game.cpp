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
	HDC hMemdc = CreateCompatibleDC(hdc); // ȭ��dc(�׸� ������) ��� �޸� DC���� 
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, r.right, r.bottom); // ��Ʈ�� ����
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemdc, hBitmap); // ��Ʈ�� ����


	RenderInfo ri{ hWnd, hMemdc, m_hInst, {(LONG)((double)r.right * 0.5), (LONG)((double)r.bottom * 0.5)}, {r.right, r.bottom} };
	UpdateInfo ui{ deltaTime, m_hInst };

	m_currentScene->Loop(ui, ri);
	Debug::Render(ri);

	BitBlt(hdc, 0, 0, r.right, r.bottom, hMemdc, 0, 0, SRCCOPY); // ��Ӻ��� hMemdc->hdc
	SelectObject(hMemdc, hOldBitmap); // ���� ��Ʈ�� ����
	ReleaseDC(hWnd, hMemdc); // �޸� dc ����
	DeleteObject(hOldBitmap);
	DeleteObject(hBitmap);

	Input::Update();
}

HINSTANCE Game::GethInstance()
{
	return m_hInst;
}