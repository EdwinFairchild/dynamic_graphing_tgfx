#ifndef GRAPHING_SCREENVIEW_HPP
#define GRAPHING_SCREENVIEW_HPP

#include <gui_generated/graphing_screen_screen/graphing_ScreenViewBase.hpp>
#include <gui/graphing_screen_screen/graphing_ScreenPresenter.hpp>
#include "stdint.h"
#include "stdbool.h"
#include <math.h>
class graphing_ScreenView : public graphing_ScreenViewBase
{
public:
    graphing_ScreenView();
    virtual ~graphing_ScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void buttonSpeed();
    virtual void handleTickEvent();
    virtual void rotateAroundCenter(int16_t current_x, int16_t currnet_y, float theta);
    uint32_t tickCounter;
    bool animate_speed_highLight = false;

protected:
};

#endif // GRAPHING_SCREENVIEW_HPP
