#ifndef CLICKABLE_IMAGE_WINDOW_H
#define CLICKABLE_IMAGE_WINDOW_H

#include "BaseWindow.h"

class ClickableImageWindow : public BaseWindow<ClickableImageWindow>
{
public:
    PCWSTR  className() const;
    LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

    ClickableImageWindow()=delete;
    ClickableImageWindow(LPCWSTR imageColor, LPCWSTR imageMask);
private:

    LPCWSTR m_imageColor;
    LPCWSTR m_imageMask;
    int m_imageHeight{750}; 
    int m_imageWidth{1000}; 

    //Helper function for region creation
    void setRgnFromBitMask();
};

#endif