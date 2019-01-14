#include "base.h"

namespace msg {
int Base::s_nextStackIndex = 0;
int Base::s_classStackIndex = -1;

Base::Base() {}

int
Base::createStackIndex()
{
    return s_nextStackIndex++;
}
}
