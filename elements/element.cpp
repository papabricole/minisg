#include "element.h"

namespace msg {
int Element::nextStackIndex = 0;
int Element::classStackIndex = -1;

Element::Element() {}
Element::~Element() {}

int
Element::createStackIndex()
{
    return nextStackIndex++;
}
}
