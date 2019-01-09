#pragma once

#include <base.h>

namespace msg {

#define VISITOR_ACCEPT(classname)                                                                  \
  public:                                                                                          \
    virtual std::string className() const override { return #classname; }                          \
    virtual void accept(Action* action) override { action->visit(this); }

class Node : public Base
{
    VISITOR_ACCEPT(Node)
  public:
    Node();

  protected:
    virtual ~Node();
};
}
