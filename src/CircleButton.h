#ifndef CIRCLE_BUTTON_H
#define CIRCLE_BUTTON_H

#include "BaseWindow.h"

class CircleButton : public BaseWindow<CircleButton>
{
public:
    PCWSTR  className() const;
    LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

    CircleButton(int x1,int y1,int x2,int y2);
    CircleButton(int x1,int y1,int x2,int y2, COLORREF color);
    CircleButton()=delete;

    void changeButtonFillColor(COLORREF newColor);
private:
    int m_x1;
    int m_y1;
    int m_x2;
    int m_y2;
    COLORREF m_buttonFillColor;

};

#endif