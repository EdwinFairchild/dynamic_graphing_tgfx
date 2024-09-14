#ifndef RIGHT_CONTAINER_HPP
#define RIGHT_CONTAINER_HPP

#include <gui_generated/containers/right_containerBase.hpp>

class right_container : public right_containerBase
{
public:
    right_container();
    virtual ~right_container() {}
    virtual void setTempProgressValue(int value);
    virtual void setAlpha(uint8_t alpha);



    virtual void initialize();
protected:
};

#endif // RIGHT_CONTAINER_HPP
