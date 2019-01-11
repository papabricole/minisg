#include "node.h"
#include <element.h>

namespace msg {
std::vector<Element*> Node::m_elements;

Node::Node()
{
    static bool firstInstance = true;
    if (firstInstance) {
        m_elements.resize(Element::getNumStackIndices(), nullptr);
        firstInstance = false;
    }
}
Node::~Node() {}
}
