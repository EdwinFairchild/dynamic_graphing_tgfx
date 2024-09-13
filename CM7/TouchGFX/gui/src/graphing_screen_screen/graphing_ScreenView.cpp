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
    gauge1.setValue(map_float(0,0.0,200.0,16.0,92.0)); 
    gauge1.setAlpha(0);
    circle.setAlpha(0);
    background.setAlpha(0);
    //invalidate all 3
    gauge1.invalidate();
    circle.invalidate();
    background.invalidate();

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
void graphing_ScreenView::allVisibleDone()
{
    // initiate the intro animation
    playIntro++;
}
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
    //-------------| 
    static int incr = 1;
    static int gaugeVal = 0;
    if(playIntro == 1)
    {
        // gauge1.setValue(map_float(60.0,0.0,100.0,16.0,92.0));
        if(incr < 50){
            //gauge1.setValue(gaugeVal);
            gauge1.setValue(map_float((float)gaugeVal,0.0,200.0,16.0,92.0));
            battery_level.setValue(gaugeVal);
            incr++;
            gaugeVal+=5;
        }else
        {
            gauge1.setValue(map_float((float)gaugeVal,0.0,200.0,16.0,92.0));
             battery_level.setValue(gaugeVal);
            gaugeVal -=5;
            if(gaugeVal < 5)
            { 
                gauge1.setValue(map_float(0.0,0.0,200.0,16.0,92.0));
                 battery_level.setValue(gaugeVal);
                playIntro++;
            }
        }
    }

    // incrmement digitalClock1 every second
    if (tickCounter % 60 == 0)
    {
        if (++digitalSeconds >= 60)
        {
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
