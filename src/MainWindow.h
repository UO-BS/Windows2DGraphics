#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "BaseWindow.h"

class MainWindow : public BaseWindow<MainWindow>
{
public:
    PCWSTR  className() const;
    LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};


#endif