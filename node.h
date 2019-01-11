#pragma once

#include <base.h>

#include <vector>

namespace msg {

class Element;

#define NODE_HEADER(classname)                                                                     \
  public:                                                                                          \
    virtual std::string className() const override { return #classname; }                          \
    static int s_classStackIndex;                                                                  \
    static int getClassStackIndex() { return s_classStackIndex; }                                  \
    virtual int classStackIndex() const override { return classname::s_classStackIndex; }

#define NODE_SOURCE(classname) int classname::s_classStackIndex = Node::createStackIndex();

class Node : public Base
{
    NODE_HEADER(Node)
  public:
    Node();

    virtual void render() {}

    static std::vector<msg::Element*> m_elements;

    static int getNumStackIndices() { return s_nextStackIndex; }

  protected:
    virtual ~Node();
};
}
