#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tchar.h>
#include <string>
#include <tuple>
#include <sstream>
#include <vector>
#include "Info.h"
#include "Camera.h"
#include "type.h"

class Debug
{
private:
	static HANDLE m_console;
	static std::vector<std::tuple<Vector, Vector, COLORREF>> m_rects;
	static std::vector<std::tuple<Vector, Vector, COLORREF>> m_lines;
	static std::vector<std::tuple<Vector, float, COLORREF>> m_circles;

	static void _DrawRect(const Vector& pos, const Vector& size, COLORREF color, const RenderInfo& info)
	{
		IVector s = size * 0.5;

		HGDIOBJ old = SelectObject(info.hdc, CreatePen(PS_SOLID, 1, color));
		HPEN pen = (HPEN)SelectObject(info.hdc, GetStockObject(NULL_BRUSH));

		IVector v = Camera::WorldToScreen(pos, info);

		Rectangle(info.hdc, v.x - s.x, v.y - s.y, v.x + s.x, v.y + s.y);

		DeleteObject(SelectObject(info.hdc, old));
		DeleteObject(pen);
	}

	static void _DrawLine(const Vector& start, const Vector& end, COLORREF color, const RenderInfo& info)
	{
		HGDIOBJ old = SelectObject(info.hdc, CreatePen(PS_SOLID, 1, color));

		IVector v1 = Camera::WorldToScreen(start, info);
		IVector v2 = Camera::WorldToScreen(end, info);

		MoveToEx(info.hdc, v1.x, v1.y, NULL);
		LineTo(info.hdc, v2.x, v2.y);

		DeleteObject(SelectObject(info.hdc, old));
	}
	static void _DrawCircle(const Vector& pos, float radius, COLORREF color, const RenderInfo& info)
	{
		HGDIOBJ old = SelectObject(info.hdc, CreatePen(PS_SOLID, 1, color));
		HPEN pen = (HPEN)SelectObject(info.hdc, GetStockObject(NULL_BRUSH));

		Vector ltw = pos + Vector(-radius, -radius);
		Vector rbw = pos + Vector(radius, radius);

		IVector lt = Camera::WorldToScreen(ltw, info);
		IVector rb = Camera::WorldToScreen(rbw , info);

		Ellipse(info.hdc, lt.x, lt.y, rb.x, rb.y);

		DeleteObject(SelectObject(info.hdc, old));
		DeleteObject(pen);
	}


public:
	static void Initialize()
	{
		AllocConsole();
		m_console = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	static void Render(const RenderInfo& ri)
	{
		for (auto& i : m_rects)
		{
			_DrawRect(get<0>(i), get<1>(i), get<2>(i), ri);
		}
		for (auto& i : m_lines)
		{
			_DrawLine(get<0>(i), get<1>(i), get<2>(i), ri);
		}
		for (auto& i : m_circles)
		{
			_DrawCircle(get<0>(i), get<1>(i), get<2>(i), ri);
		}

		m_rects.clear();
		m_lines.clear();
		m_circles.clear();
	}

	static void Log(std::string str)
	{
		static DWORD dwByte(0);

		str.append("\n");

		WriteFile(m_console, str.data(), (DWORD)str.length(), &dwByte, NULL);
	}

	static void Log(int value)
	{
		static DWORD dwByte(0);

		std::stringstream ss;

		ss << value << "\n";

		std::string str = ss.str();

		WriteFile(m_console, str.data(), (DWORD)str.length(), &dwByte, NULL);
	}

	static void Log(float value)
	{
		static DWORD dwByte(0);

		std::stringstream ss;

		ss << value << "\n";

		std::string str = ss.str();

		WriteFile(m_console, str.data(), (DWORD)str.length(), &dwByte, NULL);
	}

	static void Log(Vector v)
	{
		static DWORD dwByte(0);

		std::stringstream ss;

		ss << "(" << v.x << ", " << v.y << ")\n";

		std::string str = ss.str();

		WriteFile(m_console, str.data(), (DWORD)str.length(), &dwByte, NULL);
	}

	template<int row, int col>
	static void Log(Matrix<row, col, CKMath::MathPrimitiveType> m)
	{
		DWORD dwByte(0);

		std::stringstream os;
		for (int i = 0; i < row; i++)
		{
			os << "| ";
			for (int j = 0; j < col; j++)
			{
				os << m.GetAt(i, j);
				if (j != col - 1)
					os << ", ";
				else
					os << " |";
			}
			os << "\n";
		}


		std::string str = os.str();
		WriteFile(m_console, str.data(), (DWORD)str.length(), &dwByte, NULL);
	}

	static void DrawRect(const Vector& pos, const Vector& size, COLORREF color)
	{
		m_rects.push_back({ pos, size, color });

	}

	static void DrawLine(const Vector& start, const Vector& end, COLORREF color)
	{
		m_lines.push_back({ start, end, color });
	}

	static void DrawRay(const Vector& origin, const Vector& ray, COLORREF color)
	{
		m_lines.push_back({ origin, origin + ray, color });
	}

	static void DrawCircle(const Vector& pos, float radius, COLORREF color)
	{
		m_circles.push_back({ pos, radius, color });
	}

	static void Release()
	{
		FreeConsole();
	}
};