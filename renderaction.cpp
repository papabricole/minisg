#include "renderaction.h"
#include "node.h"
#include "group.h"
#include "transform.h"
#include "camera.h"
#include "mesh.h"
#include "element.h"

#include "cameraelement.h"
#include "meshelement.h"

#include <iostream>

namespace msg {

RenderAction::RenderAction()
{
    std::cout << "num stack indices: " << Element::getNumStackIndices() << std::endl;
}

void
RenderAction::visit(Node* node)
{
    std::cout << node->className() << " rendered by Node" << std::endl;
}
void
RenderAction::visit(Group* node)
{
    std::cout << node->className() << " rendered by Group" << std::endl;
}
void
RenderAction::visit(Transform* node)
{
    std::cout << node->className() << " rendered by Transform" << std::endl;
}
void
RenderAction::visit(Camera* node)
{
    std::cout << node->className() << " rendered by Camera" << std::endl;
    CameraElement* ce = CameraElement::get(node);
    std::cout << "element: " << ce->className() << " stack index: " << ce->getClassStackIndex()
              << std::endl;
}
void
RenderAction::visit(Mesh* node)
{
    std::cout << node->className() << " rendered by Mesh" << std::endl;
    MeshElement* ce = MeshElement::get(node);
    std::cout << "element: " << ce->className() << " stack index: " << ce->getClassStackIndex()
              << std::endl;
}
}
