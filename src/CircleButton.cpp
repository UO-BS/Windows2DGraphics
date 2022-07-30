#ifndef UNICODE
#define UNICODE
#endif 

#include "CircleButton.h"

CircleButton::CircleButton(int x1,int y1,int x2,int y2) : BaseWindow(), m_x1{x1}, m_y1{y1}, m_x2{x2}, m_y2{y2}, m_buttonFillColor{0x00000000} {}
CircleButton::CircleButton(int x1,int y1,int x2,int y2, COLORREF color) : BaseWindow(), m_x1{x1}, m_y1{y1}, m_x2{x2}, m_y2{y2}, m_buttonFillColor{color} {}

void CircleButton::changeButtonFillColor(COLORREF newColor) {m_buttonFillColor = newColor;}

PCWSTR CircleButton::className() const{return L"CircleButton";}
LRESULT CircleButton::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        {
        LRESULT lRes = DefWindowProc(m_hwnd, uMsg, wParam, lParam);
        HRGN ellipticalRegion = CreateEllipticRgn(m_x1,m_y1,m_x2,m_y2);
        SetWindowRgn(m_hwnd,ellipticalRegion,true);
        DeleteObject(ellipticalRegion);
        return lRes;
        }

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(m_hwnd, &ps);
            
            HBRUSH brush = CreateSolidBrush(m_buttonFillColor);
            SelectObject(hdc,brush);
            Ellipse(hdc,m_x1,m_y1,m_x2,m_y2);
            
            DeleteObject(brush);
            
            EndPaint(m_hwnd, &ps);
        }
        return 0;

    case WM_LBUTTONDOWN:
        if (GetParent(m_hwnd) != NULL) {
            SendMessage(GetParent(m_hwnd), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(m_hwnd), BN_CLICKED), (LPARAM)m_hwnd);
        }
        return 0;
        

    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}