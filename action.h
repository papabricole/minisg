#pragma once

namespace msg {

class Node;

class Action
{
  public:
    Action();

    void apply(Node* root);
};
}
