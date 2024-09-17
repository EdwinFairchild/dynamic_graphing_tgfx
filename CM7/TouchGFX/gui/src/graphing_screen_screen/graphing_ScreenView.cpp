#include <gui/graphing_screen_screen/graphing_ScreenView.hpp>
#define WIDTH  100  // Width of the square image
#define HEIGHT 100  // Height of the square image
graphing_ScreenView::graphing_ScreenView()
{

}
//------------------------------------------------------------------------------------------------
void graphing_ScreenView::setupScreen()
{
    graphing_ScreenViewBase::setupScreen();
    currentIntro = INTRO_NONE;
    gauge1.setValue(map_float(0,0.0,200.0,16.0,92.0)); 
    gauge1.setAlpha(0);
    right_container1.setAlpha(0);
    battery_level.setAlpha(0);
    circle.setAlpha(0);
    background.setAlpha(0);
    //invalidate all 3
    gauge1.invalidate();
    circle.invalidate();
    background.invalidate();
    battery_level.invalidate();
    right_container1.invalidate();

    digitalHours = digitalClock1.getCurrentHour();
    digitalMinutes = digitalClock1.getCurrentMinute();
    digitalSeconds = digitalClock1.getCurrentSecond();

}
//------------------------------------------------------------------------------------------------
void graphing_ScreenView::tearDownScreen()
{
    graphing_ScreenViewBase::tearDownScreen();
}
//------------------------------------------------------------------------------------------------
float graphing_ScreenView::map_float(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
//------------------------------------------------------------------------------------------------
void graphing_ScreenView::sliderValueChanged(int value)
{
    uint16_t speed = value;
    Unicode::snprintf(mphBuffer, 10, "%d", (int)speed);
    touchgfx::colortype slowColor = touchgfx::Color::getColorFromRGB(102,102,102);
    touchgfx::colortype mediumColor = touchgfx::Color::getColorFromRGB(0,126,0);
    touchgfx::colortype fastColor = touchgfx::Color::getColorFromRGB(200,0,0);
    // map image and gauge values are not 1:1 so we need to map the speed to the gauge value
    gauge1.setValue(map_float(speed,0.0,210.0,16.0,92.0)); 
    battery_level.setValue(speed);
    right_container1.setTempProgressValue(speed);
    right_container1.setLeftGaugeValue(speed);
    // MPH Color depending on speed
    if(speed < 80){
        mph.setColor(slowColor);
    }
    else if(speed < 145){
        mph.setColor(mediumColor);
    }
    else{
        mph.setColor(fastColor);
    }

    // for redraw of widgets
    mph.invalidate();
    gauge1.invalidate();
 
}
//------------------------------------------------------------------------------------------------
void graphing_ScreenView::handleTickEvent()
{
	tickCounter++;
    if(currentIntro != INTRO_NONE){
        runIntros();
    }
    updateClock();
}
//------------------------------------------------------------------------------------------------
void graphing_ScreenView::updateClock()
{
    // incrmement digitalClock1 every second
    if (tickCounter % 60 == 0)
    {
        if (++digitalSeconds >= 60){
            digitalSeconds = 0;
            if (++digitalMinutes >= 60)
            {
                digitalMinutes = 0;
                if (++digitalHours >= 24)
                {
                    digitalHours = 0;
                }
            }
        }
        // Update the clock
        digitalClock1.setTime24Hour(digitalHours, digitalMinutes, digitalSeconds);
    }
}
//------------------------------------------------------------------------------------------------
void graphing_ScreenView::backGroundAnimationDone()
{
    // run the intro animation
    currentIntro = INTRO_ELEMENTS;
}

void graphing_ScreenView::runIntros()
{
    static int incr = 0;
    // run the intro animation
    switch (currentIntro)
    {

    case INTRO_ELEMENTS:
        if(incr <=255)
        {
            right_container1.setAlpha(incr);
            battery_level.setAlpha(incr);
            right_container1.invalidate();
            battery_level.invalidate();
            incr+=5;
        }
        else
        {
            incr = 0;
            currentIntro = INTRO_GAUGE_UP;
        }
        break;
    case INTRO_GAUGE_UP:
        if((incr < 210))
        {
            //gauge1.setValue(gaugeVal);
            gauge1.setValue(map_float((float)incr,0.0,200.0,16.0,92.0));
            incr+=10;
        }
        else
        {
            incr = 200;
            currentIntro = INTRO_GAUGE_DOWN;
        }
        
        break;
    case INTRO_GAUGE_DOWN:
        if((incr > 0))
        {
            //gauge1.setValue(gaugeVal);
            gauge1.setValue(map_float((float)incr,0.0,200.0,16.0,92.0));
            incr-=10;
        }
        else
        {
            gauge1.setValue(map_float(0.0,0.0,200.0,16.0,92.0));
            currentIntro = INTRO_NONE;
           
        }
        break;
    
    default:
        break;
    }
}