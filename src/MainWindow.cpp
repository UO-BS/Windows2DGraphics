#ifndef UNICODE
#define UNICODE
#endif 

#include "MainWindow.h"
#include <iostream>

PCWSTR  MainWindow::className() const { return L"MainWindow"; }
LRESULT MainWindow::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        {
        LRESULT lRes = DefWindowProc(m_hwnd, uMsg, wParam, lParam);
        
        CreateWindowEx(0, L"BUTTON", L"MyBtn", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 0,0,100,100,m_hwnd,(HMENU)1,GetModuleHandle(NULL),NULL);
        CreateWindowEx(0, L"BUTTON", L"MyBtn2", WS_CHILD | WS_VISIBLE, 100,100,100,100,m_hwnd,(HMENU)2,GetModuleHandle(NULL),NULL);
        CreateWindowEx(0, L"STATIC", L"MyLabel", WS_CHILD | WS_VISIBLE, 200,200,100,100,m_hwnd,(HMENU)3,GetModuleHandle(NULL),NULL);
        //Having different dimensions than the myCircleButton object will crop it
        myCircleButton.create(L"MyCircleButton",WS_CHILD | WS_VISIBLE,0,300,300,100,100,m_hwnd,(HMENU)4);

        return lRes;
        }

    case WM_GETMINMAXINFO:
        {
            LPMINMAXINFO minMaxInfo = (LPMINMAXINFO)lParam;
            minMaxInfo->ptMinTrackSize.x = 500;
            minMaxInfo->ptMinTrackSize.y = 500;
        }
        return 0;

    case WM_COMMAND:
        switch(LOWORD(wParam)){
            case 1: //If message was from first control
                std::cout << "1";
                break;
            case 2: //If message was from second control
                std::cout << "2";
                break;
            case 4: //If message was from second control
                std::cout << "4";
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