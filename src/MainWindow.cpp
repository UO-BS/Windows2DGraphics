#ifndef UNICODE
#define UNICODE
#endif 

#include "MainWindow.h"
#include <iostream>

PCWSTR  MainWindow::className() const { return L"Sample Window Class"; }
LRESULT MainWindow::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        CreateWindowEx(0, L"BUTTON", L"MyBtn", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 0,0,100,100,m_hwnd,(HMENU)1,GetModuleHandle(NULL),NULL);
        CreateWindowEx(0, L"BUTTON", L"MyBtn2", WS_CHILD | WS_VISIBLE, 100,100,100,100,m_hwnd,(HMENU)2,GetModuleHandle(NULL),NULL);
        return 0;

    case WM_COMMAND:
        switch(LOWORD(wParam)){
            case 1:
                std::cout << "1";
                break;
            case 2:
                std::cout << "2";
                break;
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0); //Exits the message while loop, ending the program
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(m_hwnd, &ps);
            
            HBRUSH brush = CreateSolidBrush(0x000000FF);
            FillRect(hdc, &ps.rcPaint, brush);
            DeleteObject(brush);
            
            EndPaint(m_hwnd, &ps);
        }
        return 0;

    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}