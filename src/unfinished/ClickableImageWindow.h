#ifndef CLICKABLE_IMAGE_WINDOW_H
#define CLICKABLE_IMAGE_WINDOW_H

#include "BaseWindow.h"

class ClickableImageWindow : public BaseWindow<ClickableImageWindow>
{
public:
    PCWSTR  className() const;
    LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

    ClickableImageWindow()=delete;
    ClickableImageWindow(HBITMAP imageColor, HBITMAP imageMask);
private:

    HBITMAP m_imageColor;
    HBITMAP m_imageMask;
    int m_imageHeight;
    int m_imageWidth;

    //Helper function for region creation
    HRGN getRgnFromBitMask();
};

#endif