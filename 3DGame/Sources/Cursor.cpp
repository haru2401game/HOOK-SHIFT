#include "pch.h"
#include "Cursor.h"

bool Cursor::m_isLocked = false;
bool Cursor::m_isVisible = true;

void Cursor::Update(HWND hwnd)
{
    if (!m_isLocked || !hwnd)
    {
        return;
    }

    RECT rect;
    GetClientRect(hwnd, &rect);

    POINT center;
    center.x = (rect.left + rect.right) / 2;
    center.y = (rect.top + rect.bottom) / 2;

    ClientToScreen(hwnd, &center);

    SetCursorPos(center.x, center.y);
}

void Cursor::Show()
{
    OutputDebugStringA("Cursor Show\n");

    while (ShowCursor(TRUE) < 0)
    {
    }

    m_isVisible = true;
}

void Cursor::Hide()
{
    OutputDebugStringA("Cursor Hide\n");

    while (ShowCursor(FALSE) >= 0)
    {
    }

    m_isVisible = false;
}

void Cursor::LockToCenter()
{
    m_isLocked = true;
}

void Cursor::Unlock()
{
    m_isLocked = false;
}

bool Cursor::IsVisible()
{
    return m_isVisible;
}