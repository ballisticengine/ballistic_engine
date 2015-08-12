#include <limits.h>
#include <gtest/gtest.h>
#include "python/scripting.hpp"

TEST(Scripting, ScriptingTest) {
    PyScripting *scripting = PyScripting::getInstance();
    scripting->loadManipulators();
    scripting->broadcast("self_load");
    scripting->broadcast("dupa");
}
