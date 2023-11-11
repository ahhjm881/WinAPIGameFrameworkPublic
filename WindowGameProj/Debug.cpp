#include "Debug.h"

HANDLE Debug::m_console = 0;
std::vector<std::tuple<Vector, Vector, COLORREF>> Debug::m_rects = {};
std::vector<std::tuple<Vector, Vector, COLORREF>> Debug::m_lines = {};
std::vector<std::tuple<Vector, float, COLORREF>> Debug::m_circles = {};