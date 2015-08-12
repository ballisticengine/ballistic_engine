#include <limits.h>
#include <gtest/gtest.h>
#include "config/KeyBindings.hpp"

TEST(ConfigTest, ConfigMainClassTest) {
    
}

TEST(ConfigTest, KeyBindingsTest) {
    KeyBindings *kb = new KeyBindings("data/keybindings.xml");
    bool load_result = kb->loadBindings();
    
}
