#include "renderer/actions/RenderUI.hpp"

#include "ui/ui.hpp"


void RenderUI::render() {
    this->renderer->resetMatrix();
    UI::getInstance()->getContext()->Render();
    UI::getInstance()->getContext()->Update();
}