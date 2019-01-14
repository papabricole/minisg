#pragma once

#include <vector>

namespace msg {

class Element;

class State
{
  public:
    State();

    void push();
    void pop();

    std::vector<msg::Element*> m_elements;
};
}
