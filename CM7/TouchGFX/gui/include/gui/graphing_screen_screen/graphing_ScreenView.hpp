#ifndef GRAPHING_SCREENVIEW_HPP
#define GRAPHING_SCREENVIEW_HPP

#include <gui_generated/graphing_screen_screen/graphing_ScreenViewBase.hpp>
#include <gui/graphing_screen_screen/graphing_ScreenPresenter.hpp>

class graphing_ScreenView : public graphing_ScreenViewBase
{
public:
    graphing_ScreenView();
    virtual ~graphing_ScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // GRAPHING_SCREENVIEW_HPP
