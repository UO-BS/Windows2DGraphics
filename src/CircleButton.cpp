#ifndef UNICODE
#define UNICODE
#endif 

#include "CircleButton.h"

PCWSTR CircleButton::className() const{return L"CircleButton";}
LRESULT CircleButton::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    
    //case WM_CREATE:
        //Set Window Region
        //return 0;
    
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(m_hwnd, &ps);
            
            SelectObject(hdc,GetStockObject(BLACK_PEN));
            Ellipse(hdc,0,0,100,100);
            
            EndPaint(m_hwnd, &ps);
        }
        return 0;

    case WM_LBUTTONDOWN:
        SendMessage(GetParent(m_hwnd), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(m_hwnd), BN_CLICKED), (LPARAM)m_hwnd);
        return 0;
        

    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}