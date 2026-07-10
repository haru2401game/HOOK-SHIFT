#pragma once

#include "pch.h"

class Input
{
public:
    static void Update(HWND hwnd);

    static bool GetKey(int key);
    static bool GetKeyDown(int key);
    static bool GetKeyUp(int key);

    static int GetMouseDeltaX();
    static int GetMouseDeltaY();

private:
    static bool m_current[256];
    static bool m_previous[256];

    static int m_mouseDeltaX;
    static int m_mouseDeltaY;
};