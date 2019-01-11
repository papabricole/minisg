#pragma once

#include <node.h>

#include <string>
#include <iostream>

namespace msg {

#define ELEMENT_HEADER(classname)                                                                  \
  public:                                                                                          \
    virtual std::string className() const override { return #classname; }                          \
    static int classStackIndex;                                                                    \
    static int getClassStackIndex() { return classStackIndex; }                                    \
    static classname* get(Node* node)                                                              \
    {                                                                                              \
        classname* elt = static_cast<classname*>(node->m_elements[classStackIndex]);               \
        if (!elt) {                                                                                \
            std::cout << "creating new element for " << node->className() << std::endl;            \
            elt = new classname;                                                                   \
            node->m_elements[classStackIndex] = elt;                                               \
        }                                                                                          \
        return elt;                                                                                \
    }

#define ELEMENT_SOURCE(classname) int classname::classStackIndex = Element::createStackIndex();

class Element
{
  public:
    Element();
    virtual ~Element();

    virtual std::string className() const = 0;

    static int getNumStackIndices() { return nextStackIndex; }

  protected:
    static int nextStackIndex;
    static int classStackIndex;
    static int createStackIndex();
};
}
