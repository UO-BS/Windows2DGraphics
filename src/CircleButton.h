#ifndef CIRCLE_BUTTON_H
#define CIRCLE_BUTTON_H

#include "BaseWindow.h"

class CircleButton : public BaseWindow<CircleButton>
{
public:
    PCWSTR  className() const;
    LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
private:

};

#endif