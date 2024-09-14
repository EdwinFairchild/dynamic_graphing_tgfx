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

void right_container::setAlpha(uint8_t alpha) {
    temp_progress.setAlpha(alpha);
    temp_text_area.setAlpha(alpha);
    temp_progress.invalidate();
    temp_text_area.invalidate();
}

