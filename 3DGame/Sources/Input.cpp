#include "pch.h"
#include "Input.h"

bool Input::m_current[256] = {};
bool Input::m_previous[256] = {};

int Input::m_mouseDeltaX = 0;
int Input::m_mouseDeltaY = 0;

void Input::Update(HWND hwnd)
{
    memcpy(m_previous, m_current, sizeof(m_current));

    for (int i = 0; i < 256; i++)
    {
        m_current[i] = GetAsyncKeyState(i) & 0x8000;
    }

    RECT rc;
    GetClientRect(hwnd, &rc);

    POINT center;
    center.x = (rc.right - rc.left) / 2;
    center.y = (rc.bottom - rc.top) / 2;

    ClientToScreen(hwnd, &center);

    POINT mouse;
    GetCursorPos(&mouse);

    m_mouseDeltaX = mouse.x - center.x;
    m_mouseDeltaY = mouse.y - center.y;
}

bool Input::GetKey(int key)
{
    return m_current[key];
}

bool Input::GetKeyDown(int key)
{
    return m_current[key] && !m_previous[key];
}

bool Input::GetKeyUp(int key)
{
    return !m_current[key] && m_previous[key];
}

int Input::GetMouseDeltaX()
{
    return m_mouseDeltaX;
}

int Input::GetMouseDeltaY()
{
    return m_mouseDeltaY;
}