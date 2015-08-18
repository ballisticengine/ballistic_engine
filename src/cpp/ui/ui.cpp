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

    VideoData *vd = Config::getInstance()->getVD();
    context = Rocket::Core::CreateContext("default",
            Rocket::Core::Vector2i(4, 4));

    Rocket::Debugger::Initialise(context);
    return true;
}

void UI::showTestUi() {
    Rocket::Core::ElementDocument *Document = context->LoadDocument("demo.rml");
    if (Document) {
        Document->Show();
        Document->RemoveReference();
        cout << "Document loaded" << endl;
    } else {
        cout << "Error" << endl;
    }
}

RC::Context *UI::getContext() {
    return this->context;
}

UI::~UI() {
    Rocket::Core::Shutdown();
}