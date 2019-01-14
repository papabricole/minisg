#pragma once

#include <action.h>
#include <string>

namespace msg {

class Base
{
  public:
    Base();

    virtual std::string className() const = 0;
    virtual int classStackIndex() const = 0;

  protected:
    static int s_nextStackIndex;
    static int s_classStackIndex;
    static int createStackIndex();
};
}
