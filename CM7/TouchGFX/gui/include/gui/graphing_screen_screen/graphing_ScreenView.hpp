#ifndef GRAPHING_SCREENVIEW_HPP
#define GRAPHING_SCREENVIEW_HPP

#include <gui_generated/graphing_screen_screen/graphing_ScreenViewBase.hpp>
#include <gui/graphing_screen_screen/graphing_ScreenPresenter.hpp>
#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"
#include <math.h>
#include <stdlib.h>
#include <touchgfx/Color.hpp>
class graphing_ScreenView : public graphing_ScreenViewBase
{
public:
    uint32_t tickCounter;
    volatile uint8_t playIntro = 0;
    int digitalHours;
    int digitalMinutes;
    int digitalSeconds;
    graphing_ScreenView();
    virtual ~graphing_ScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
    virtual void sliderValueChanged(int value);
    virtual void allVisibleDone();
    virtual float map_float(float x, float in_min, float in_max, float out_min, float out_max) ;
protected:
};

#endif // GRAPHING_SCREENVIEW_HPP
