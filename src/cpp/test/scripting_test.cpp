#include <limits.h>
#include <gtest/gtest.h>
#include "python/scripting.hpp"

TEST(Scripting, ScriptingTest) {
    PyScripting *scripting = PyScripting::getInstance();
    scripting->loadManipulators();
    scripting->broadcast("self_load");
    scripting->broadcast("self_load",{0},true);
    scripting->broadcast("dupa", {0}, true);
    
}

TEST(Scripting, ManipulatorTest) {
     PyScripting *scripting = PyScripting::getInstance();
     PyManipulator *man = scripting->getManipulator("TestManipulator");
    ASSERT_NE(0, (unsigned long) man);
    ASSERT_EQ(1, (int)man->hasSignal("self_load"));
    ASSERT_EQ(0, (int)man->hasSignal("dupa"));
     
}