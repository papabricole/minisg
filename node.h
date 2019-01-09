#pragma once

#include <base.h>

namespace msg {

#define NODE_HEADER(classname)                                                                     \
  public:                                                                                          \
    virtual std::string className() const override { return #classname; }

class Node : public Base
{
    NODE_HEADER(Node)
  public:
    Node();

    void render() {}

  protected:
    virtual ~Node();
};
}
