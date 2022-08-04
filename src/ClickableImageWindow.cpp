#ifndef UNICODE
#define UNICODE
#endif 

#include "ClickableImageWindow.h"
#include <iostream>

ClickableImageWindow::ClickableImageWindow(LPCWSTR imageColor, LPCWSTR imageMask) : BaseWindow(), m_imageColor{imageColor}, m_imageMask{imageMask} {}

PCWSTR ClickableImageWindow::className() const{return L"CircleButton";}

LRESULT ClickableImageWindow::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        {
        LRESULT lRes = DefWindowProc(m_hwnd, uMsg, wParam, lParam);
        setRgnFromBitMask();
        return lRes;
        }

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(m_hwnd, &ps);
            
            
            HBITMAP bmpColor = (HBITMAP) LoadImage(NULL,m_imageColor,IMAGE_BITMAP,m_imageWidth,m_imageHeight,LR_LOADFROMFILE);
            if (!bmpColor) {
                std::cout << "Error Loading .bmp file: " << GetLastError() << "\n";
                std::cout << "Image path: " << m_imageColor << "\n";
            }
            HDC tempDC = CreateCompatibleDC(hdc);
            HGDIOBJ replacedOBJ = SelectObject(tempDC, bmpColor);
            BitBlt(hdc,0,0,m_imageWidth,m_imageHeight,tempDC,0,0,SRCCOPY);
            SelectObject(tempDC, replacedOBJ);
            DeleteObject(bmpColor);
            DeleteDC(tempDC);
            

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


void ClickableImageWindow::setRgnFromBitMask()
{
    HRGN hRgn = CreateRectRgn(0,0,0,0); //CHANGE 10s TO 0, THIS WAS FOR TESTING

    //Load mask and DCs
    HDC clientDC = GetDC(m_hwnd);
    HBITMAP bmpMask = (HBITMAP) LoadImage(NULL,m_imageMask,IMAGE_BITMAP,m_imageWidth,m_imageHeight,LR_LOADFROMFILE);
    if (!bmpMask) {
        std::cout << "Error Loading .bmp file: " << GetLastError() << "\n";
        std::cout << "Image path: " << m_imageMask << "\n";
    }
    HDC tempDC = CreateCompatibleDC(clientDC);
    HGDIOBJ replacedOBJ = SelectObject(tempDC, bmpMask);

    //Creating the Region
    //Current Region creation method: Add each pixel individually
    for (int y=0;y<m_imageHeight;y++) {
        for (int x=0;x<m_imageWidth;x++) {
            
            if (GetPixel(tempDC,x,y) == 0x00000000) {
                HRGN tempRectRgn = CreateRectRgn(x,y,x+1,y+1); //This could be put outside the loop? Not sure if CreateRectRgn must be deleted every time
                CombineRgn(hRgn,hRgn,tempRectRgn,RGN_OR); //RGN_DIFF might be faster?
                DeleteObject(tempRectRgn);      //This could be put outside the loop? Not sure if CreateRectRgn must be deleted every time
            }
        }
    }
    /*  Alternative Region creation (Horizontal style):
        -Find next black pixel in row (this could be first pixel)
        -Find next white pixel in row
        -Create a rectangle from first black to next white and merge with hRgn
        -repeat until end of row
        -move to next row
    */

    SetWindowRgn(m_hwnd,hRgn,true);

    //Cleaning up
    SelectObject(tempDC, replacedOBJ);
    DeleteObject(bmpMask);
    DeleteDC(tempDC);
    ReleaseDC(m_hwnd, clientDC);

    DeleteObject(hRgn);
}