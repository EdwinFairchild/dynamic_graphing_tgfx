#include <gui/containers/right_container.hpp>

right_container::right_container()
{

}

void right_container::initialize()
{
    right_containerBase::initialize();
}

void right_container::setTempProgressValue(int value) {
        temp_progress.setValue(value);
        temp_progress.invalidate();
}
int right_container::getTempProgressValue(void) {
        return temp_progress.getValue();
}

void right_container::setLeftGaugeValue(int value) {
    gauge_left_progress.setValue(value);
    gauge_left_progress.invalidate();
}

void right_container::setAlpha(uint8_t alpha) {
    temp_progress.setAlpha(alpha);
    temp_text_area.setAlpha(alpha);
    gauge_left_progress.setAlpha(alpha);
    temp_progress.invalidate();
    temp_text_area.invalidate();
    gauge_left_progress.invalidate();
}