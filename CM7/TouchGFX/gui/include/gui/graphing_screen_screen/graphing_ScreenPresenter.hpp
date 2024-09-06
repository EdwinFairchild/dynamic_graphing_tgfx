#ifndef GRAPHING_SCREENPRESENTER_HPP
#define GRAPHING_SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class graphing_ScreenView;

class graphing_ScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    graphing_ScreenPresenter(graphing_ScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~graphing_ScreenPresenter() {}

private:
    graphing_ScreenPresenter();

    graphing_ScreenView& view;
};

#endif // GRAPHING_SCREENPRESENTER_HPP
