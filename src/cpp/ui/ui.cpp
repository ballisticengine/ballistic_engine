#include "ui/ui.hpp"

bool UI::init(RC::SystemInterface *system_interface,
        RC::RenderInterface *rc_renderer_interface,
        RC::FileInterface *file_interface,
        RendererInterface *renderer_interface) {

    this->system_interface = system_interface;
    this->rc_renderer_interface = rc_renderer_interface;
    this->file_interface = file_interface;
    this->renderer = renderer_interface;

    Rocket::Core::SetFileInterface(file_interface);
    Rocket::Core::SetRenderInterface(rc_renderer_interface);
    Rocket::Core::SetSystemInterface(system_interface);

    if (!Rocket::Core::Initialise()) {
        return false;
    }

    Rocket::Core::FontDatabase::LoadFontFace("Delicious-Bold.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Delicious-BoldItalic.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Delicious-Italic.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Delicious-Roman.otf");

    VideoData *vd = Config::getInstance()->getVD();
    context = Rocket::Core::CreateContext("default",
            Rocket::Core::Vector2i(
            renderer->getFrustum().getWidth(),
            renderer->getFrustum().getHeight())
            );

    Rocket::Debugger::Initialise(context);
    return true;
}

void UI::showTestUi() {
    Rocket::Core::ElementDocument *a = context->LoadDocument("demo.rml");
    Rocket::Core::ElementDocument *b = context->LoadDocument("test.rml");

    a->Show();
    a->RemoveReference();
    b->Show();
    b->RemoveReference();

}

void UI::addElement(std::string file) {

}

RC::Context *UI::getContext() {
    return this->context;
}

UI::~UI() {
    //TODO: cleanup
    Rocket::Core::Shutdown();
}