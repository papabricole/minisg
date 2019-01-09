#include "renderaction.h"
#include "node.h"
#include "group.h"
#include "camera.h"

#include <iostream>

namespace msg {

RenderAction::RenderAction() {}

void
RenderAction::visit(Node* node)
{
    std::cout << "Node visiting: " << node->className() << std::endl;
}

void
RenderAction::visit(Group* node)
{
    std::cout << "Group visiting: " << node->className() << std::endl;
}

void
RenderAction::visit(Camera* node)
{
    std::cout << "Camera visiting: " << node->className() << std::endl;
}
}
