#include <gui/graphing_screen_screen/graphing_ScreenView.hpp>
#define WIDTH  100  // Width of the square image
#define HEIGHT 100  // Height of the square image
graphing_ScreenView::graphing_ScreenView()
{

}

void graphing_ScreenView::setupScreen()
{
    graphing_ScreenViewBase::setupScreen();
}

void graphing_ScreenView::tearDownScreen()
{
    graphing_ScreenViewBase::tearDownScreen();
}

void graphing_ScreenView::buttonSpeed()
   {
      animate_speed_highLight = true;
   }

void graphing_ScreenView::rotateAroundCenter(int16_t current_x, int16_t currnet_y, float theta) {
    // Calculate the center point of the image
    float cx = WIDTH / 2.0;
    float cy = HEIGHT / 2.0;
    float x = (float)current_x;
    float y = (float)currnet_y;
    
    // Convert degrees to radians
    float radians = theta * (M_PI / 180.0);
    
    // Translate the point to the origin (relative to the center)
    float x_translated = x - cx;
    float y_translated = y - cy;
    
    // Apply rotation matrix
    float x_rotated = x_translated * cos(radians) - y_translated * sin(radians);
    float y_rotated = x_translated * sin(radians) + y_translated * cos(radians);
    
    // Translate back to the original position (relative to the center)
    x = x_rotated + cx;
    y = y_rotated + cy;
    // SpeedBright.setX(x);
    // SpeedBright.setY(y);
    // SpeedBright.clearMoveAnimationEndedAction();
    // SpeedBright.startMoveAnimation((int16_t)x, (int16_t)y, 60, touchgfx::EasingEquations::sineEaseOut, touchgfx::EasingEquations::sineEaseOut);
    // SpeedBright.invalidate();
}


void graphing_ScreenView::handleTickEvent()
{
	tickCounter++;
    static int incr = 1;

    if (gauge1.getValue() <= 0)
    {
        incr = +5;
    }
    else if (gauge1.getValue() >= 100)
    {
        incr = -5;
    }

    gauge1.setValue(gauge1.getValue() + incr);
   
    

}
