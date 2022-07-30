#ifndef UNICODE
#define UNICODE
#endif 

#include "ClickableImageWindow.h"

ClickableImageWindow::ClickableImageWindow(HBITMAP imageColor, HBITMAP imageMask) : BaseWindow(), m_imageColor{imageColor}, m_imageMask{imageMask} {}

PCWSTR ClickableImageWindow::className() const{return L"CircleButton";}

LRESULT ClickableImageWindow::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        {
        LRESULT lRes = DefWindowProc(m_hwnd, uMsg, wParam, lParam);
        //SET THE REGION HERE USING M_IMAGEMASK
        return lRes;
        }

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(m_hwnd, &ps);
            //PAINT THE REGION HERE USING M_IMAGECOLOR
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


HRGN ClickableImageWindow::getRgnFromBitMask()
{
    HRGN hRgn = CreateRectRgn(0,0,0,0);

    //Current Region creation method: Add each pixel individually
    for (int y=0;y<m_imageHeight;y++) {
        for (int x=0;x<m_imageWidth;x++) {
            //TO BE CONTINUED
        }
    }

    /*  Alternative Region creation (Horizontal style):
        -Find next black pixel in row (this could be first pixel)
        -Find next white pixel in row
        -Create a rectangle from first black to next white and merge with hRgn
        -repeat until end of row
        -move to next row
    */

}