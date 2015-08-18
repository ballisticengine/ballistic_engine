#include "ui/ui.hpp"

bool UI::init(RC::SystemInterface *system_interface,
        RC::RenderInterface *renderer_interface,
        RC::FileInterface *file_interface) {

    this->system_interface = system_interface;
    this->renderer_interface = renderer_interface;
    this->file_interface = file_interface;

    Rocket::Core::SetFileInterface(file_interface);
    Rocket::Core::SetRenderInterface(renderer_interface);
    Rocket::Core::SetSystemInterface(system_interface);

    if (!Rocket::Core::Initialise()) {
        return false;
    }

    Rocket::Core::FontDatabase::LoadFontFace("Delicious-Bold.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Delicious-BoldItalic.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Delicious-Italic.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Delicious-Roman.otf");

    //TODO: IMPORTANT!!!: move most of the logic from engine here
    VideoData *vd = Config::getInstance()->getVD();
    context = Rocket::Core::CreateContext("default",
            Rocket::Core::Vector2i(4, 4));

    Rocket::Debugger::Initialise(context);
    return true;
}

void UI::showTestUi() {
    Rocket::Core::ElementDocument *a = context->LoadDocument("demo.rml");
    Rocket::Core::ElementDocument *b = context->LoadDocument("test.rml");
    //    if (Document) {
    a->Show();
    a->RemoveReference();
    b->Show();
    b->RemoveReference();

    //    } else {
    //        cout << "Error" << endl;
    //    }
}

void UI::addElement(std:string file) {
    
}

RC::Context *UI::getContext() {
    return this->context;
}

UI::~UI() {
    //TODO: cleanup
    Rocket::Core::Shutdown();
}