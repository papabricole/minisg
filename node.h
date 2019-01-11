#pragma once

#include <base.h>

#include <vector>

namespace msg {

class Element;

#define NODE_HEADER(classname)                                                                     \
  public:                                                                                          \
    virtual std::string className() const override { return #classname; }                          \
    virtual void accept(Action* action) override { action->visit(this); }

class Node : public Base
{
    NODE_HEADER(Node)
  public:
    Node();

    virtual void render() {}

    static std::vector<msg::Element*> m_elements;

  protected:
    virtual ~Node();
};
}
