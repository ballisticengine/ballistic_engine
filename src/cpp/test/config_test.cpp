#include <limits.h>
#include <gtest/gtest.h>
#include "config/KeyBindings.hpp"

TEST(ConfigTest, ConfigMainClassTest) {
    Config *config = Config::getInstance();
    ASSERT_NE(0, (unsigned long) config->getKeyBindings());
    
    
}

TEST(ConfigTest, KeyBindingsTest) {
    KeyBindings *kb = new KeyBindings("data/keybindings.xml");
    kb->loadBindings();

}
