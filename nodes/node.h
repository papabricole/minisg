#pragma once

#include <nodes/base.h>

#include <memory>
#include <vector>

namespace msg {

#define NODE_HEADER(classname)                                                                     \
  public:                                                                                          \
    virtual std::string className() const override { return #classname; }                          \
    static std::string getClassName() { return #classname; }                                       \
    static int s_classStackIndex;                                                                  \
    static int getClassStackIndex() { return s_classStackIndex; }                                  \
    virtual int classStackIndex() const override { return classname::s_classStackIndex; }

#define NODE_SOURCE(classname) int classname::s_classStackIndex = Node::createStackIndex();

using NodeList = std::vector<std::shared_ptr<Node>>;

class Node : public Base
{
    NODE_HEADER(Node)
  public:
    Node();

    static int getNumStackIndices() { return s_nextStackIndex; }

  protected:
    virtual ~Node();

    NodeList m_children;
    friend class Action;
};
}
