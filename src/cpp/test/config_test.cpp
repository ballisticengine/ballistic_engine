#include <limits.h>
#include <gtest/gtest.h>
#include "config/KeyBindings.hpp"

TEST(KeyBindings, KeyBindingsTest) {
    KeyBindings *kb = new KeyBindings("data/keybindings.xml");
    bool load_result = kb->loadBindings();
    
}
