#pragma once

#include <Windows.h>

class Cursor
{
public:
    static void Update(HWND hwnd);

    static void Show();
    static void Hide();

    static void LockToCenter();
    static void Unlock();

    static bool IsVisible();

private:
    static bool m_isLocked;
    static bool m_isVisible;
};