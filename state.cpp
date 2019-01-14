#include "state.h"

#include <elements/element.h>

namespace msg {

State::State()
{
    m_elements.resize(Element::getNumStackIndices(), nullptr);
}

void
State::push()
{}
void
State::pop()
{}
}
