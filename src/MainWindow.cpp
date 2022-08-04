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
        myClickImage.create(L"MyClickImage", WS_CHILD | WS_VISIBLE,0,500,0,1000,1000,m_hwnd,(HMENU)5);

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
            case 1: //If message was from 1 control
                std::cout << "1";
                break;
            case 2: //If message was from 2 control
                std::cout << "2";
                break;
            case 4: //If message was from 4 control
                std::cout << "4";
                break;
            case 5: //If message was from 5 control
                std::cout << "5";
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
            
            //Color the background RED
            HBRUSH brush = CreateSolidBrush(0x000000FF);
            FillRect(hdc, &ps.rcPaint, brush);
            DeleteObject(brush);

            //Displaying an image
            HBITMAP bmp = (HBITMAP) LoadImage(NULL,m_imagePath,IMAGE_BITMAP,1000,750,LR_LOADFROMFILE);
            if (!bmp) {
                std::cout << "Error Loading .bmp file: " << GetLastError() << "\n";
                std::cout << "Image path: " << m_imagePath << "\n";
            }
            HDC tempDC = CreateCompatibleDC(hdc);
            HGDIOBJ replacedOBJ = SelectObject(tempDC, bmp);
            //BitBlt(hdc,400,400,1000,750,tempDC,0,0,SRCCOPY);
            StretchBlt(hdc,400,0,100,75,tempDC,0,0,1000,750,SRCCOPY);
            SelectObject(tempDC, replacedOBJ);
            DeleteObject(bmp);
            DeleteDC(tempDC);
            
            EndPaint(m_hwnd, &ps);
        }
        return 0;

    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}