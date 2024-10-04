#include <gui/graphing_screen_screen/graphing_ScreenView.hpp>
#define WIDTH  100  // Width of the square image
#define HEIGHT 100  // Height of the square image
graphing_ScreenView::graphing_ScreenView()
    : parkClickedCallBack(this, &graphing_ScreenView::parkClickedHandler)
{
}
//------------------------------------------------------------------------------------------------
void graphing_ScreenView::setupScreen()
{
    graphing_ScreenViewBase::setupScreen();
    currentIntro = INTRO_NONE;
    // not using this guage anymore, leaving it here because it was hard work and dont want to delete it
    // gauge1.setValue(map_float(0,0.0,200.0,16.0,92.0)); 
    // gauge1.setAlpha(0);
    // sets alpha all elements in the right container
    right_container1.setAlpha(0);
    battery_level.setAlpha(0);
    circle.setAlpha(0);
    background.setAlpha(0);
    park.setAlpha(0);
    mph.setAlpha(0);
    mph_lable.setAlpha(0);
    //invalidate all 3
    //gauge1.invalidate();
    circle.invalidate();
    background.invalidate();
    battery_level.invalidate();
    right_container1.invalidate();
    park.invalidate();
    mph.invalidate();
    mph_lable.invalidate();

    digitalHours = digitalClock1.getCurrentHour();
    digitalMinutes = digitalClock1.getCurrentMinute();
    digitalSeconds = digitalClock1.getCurrentSecond();

    park.setClickAction(parkClickedCallBack);
    drive.setClickAction(parkClickedCallBack);

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
    speed = value;
    Unicode::snprintf(mphBuffer, 10, "%d", (int)speed);
    touchgfx::colortype slowColor = touchgfx::Color::getColorFromRGB(102,102,102);
    touchgfx::colortype mediumColor = touchgfx::Color::getColorFromRGB(0,126,0);
    touchgfx::colortype fastColor = touchgfx::Color::getColorFromRGB(200,0,0);
    // map image and gauge values are not 1:1 so we need to map the speed to the gauge value
   // not using this guage anymore, leaving it here because it was hard work and dont want to delete it
   // gauge1.setValue(map_float(speed,0.0,210.0,16.0,92.0)); 

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
    updateMap();
    // Update battery and temperature levels every 2 second
    if (tickCounter % 120 == 0 && speed > 0) // Assuming 60 ticks per second
    {
        int tempScaleFactor = ((int)speed * 0.2);
        // Update the battery_level UI element, get value and subtract 1, inline
        
        battery_level.setValue(battery_level.getValue() - 1 -  ((int)speed * 0.01));
        
        battery_level.invalidate();
        // Update the temperature UI element, get value and add 1, inline
        if(right_container1.getTempProgressValue() + 1 + tempScaleFactor)
            right_container1.setTempProgressValue(100);
        else
            right_container1.setTempProgressValue(right_container1.getTempProgressValue() + 1 + tempScaleFactor);
        
    }
    // recharge when speed is zero , this is a super super charger lol
    else if(tickCounter % 60 && speed == 0 && battery_level.getValue() < 100){
        battery_level.setValue(battery_level.getValue() + 1);
        battery_level.invalidate();
    }
}
void graphing_ScreenView::updateMap()
{
    static int mapOriginalY = map_bg.getY();
  
    // Update the map every 5 seconds
    if(main_container.getSelectedPage() == 2 && tickCounter % 10 == 0)
    {
        // check if map is at the bottom
        if(map_bg.getY() > 0)
        {
            // reset map to top
            map_bg.setXY(map_bg.getX(), mapOriginalY);
            map_bg.invalidate();
        }
        // map_bg.setXY(map_bg.getX(), map_bg.getY() + 1 + ((int)(speed*0.1)));
        // map_bg.invalidate();
        // use move animator
        map_bg.clearMoveAnimationEndedAction();
        map_bg.startMoveAnimation(map_bg.getX(), map_bg.getY() + 1 + ((int)(speed*0.05)), 10);

    }
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
        if(incr <=203)
        {
            right_container1.setAlpha(incr);
            battery_level.setAlpha(incr);
            circle.setAlpha(incr);
            park.setAlpha(incr);
            mph.setAlpha(incr);
            mph_lable.setAlpha(incr);

            right_container1.invalidate();
            battery_level.invalidate();
            circle.invalidate();
            park.invalidate();
            mph.invalidate();
            mph_lable.invalidate();
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
            right_container1.setLeftGaugeValue(incr);
            battery_level.setValue(incr);
            right_container1.setTempProgressValue(incr);
            battery_level.invalidate();
            incr+=5;
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
            right_container1.setLeftGaugeValue(incr);
            battery_level.setValue(incr);
            right_container1.setTempProgressValue(incr);
            battery_level.invalidate();
            incr-=5;
        }
        else
        {
            right_container1.setLeftGaugeValue(incr);
            currentIntro = INTRO_NONE;
            battery_level.setValue(100); 
            right_container1.setTempProgressValue(50);
            
        }
        break;
    
    default:
        break;
    }
}
void graphing_ScreenView::parkClickedHandler(const FadeAnimator<Image>& b, const ClickEvent& e)
{
    if (&b == &park) 
    {
        //Implement what should happen when 'box' is touched/clicked here.
        park.clearFadeAnimationEndedAction();
        park.startFadeAnimation(0, 30);
        drive.clearFadeAnimationEndedAction();
        drive.startFadeAnimation(255, 30);
    }
    else if (&b == &drive)
    {
        //Implement what should happen when 'box' is touched/clicked here.
        drive.clearFadeAnimationEndedAction();
        drive.startFadeAnimation(0, 30);
        park.clearFadeAnimationEndedAction();
        park.startFadeAnimation(255, 30);
    }
}