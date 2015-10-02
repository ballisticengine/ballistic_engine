#include <limits.h>
#include <gtest/gtest.h>
#include "config/KeyBindings.hpp"
#include "config/EngineState.hpp"

TEST(ConfigTest, ConfigMainClassTest) {
    Config *config = Config::getInstance();
    ASSERT_NE(0, (unsigned long) config->getKeyBindings());
    
    
}

TEST(ConfigTest, KeyBindingsTest) {
    KeyBindings *kb = new KeyBindings("data/keybindings.xml");
    kb->loadBindings();

}


void callback_test(StateChangeData data) {
    cout << "callback_test" << endl;
    if(data.type==STATE_STRING) {
        cout << "data: " << *(string *)data.value << endl;
    } else {
        cout << "data: " << *(bool *)data.value << endl;
    }
    
}

TEST(EngineStateTest, EngineStateHandlerTest) {
    EngineState *es = EngineState::getInstance();
    es->setString("test","x");
    es->setStateHandler("test", callback_test);
    es->setString("test","y");
}