#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "BaseWindow.h"
#include "CircleButton.h"
#include "ClickableImageWindow.h"

class MainWindow : public BaseWindow<MainWindow>
{
private:
    CircleButton myCircleButton{0,0,100,100};
    ClickableImageWindow myClickImage{L"../resources/temp.bmp",L"../resources/tempMask.bmp"};
    LPCWSTR m_imagePath{L"../resources/temp.bmp"};
public:
    PCWSTR  className() const;
    LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};


#endif