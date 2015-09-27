#include "ui/ui.hpp"

bool UI::init(RocketSDL2SystemInterface *system_interface,
        Rocket::Core::RenderInterface *rc_renderer_interface,
        Rocket::Core::FileInterface *file_interface,
        RendererInterface *renderer_interface
        ) {

    this->system_interface = system_interface;
    this->rc_renderer_interface = rc_renderer_interface;
    this->file_interface = file_interface;
    this->renderer = renderer_interface;

    Rocket::Core::SetFileInterface(file_interface);
    Rocket::Core::SetRenderInterface(rc_renderer_interface);
    Rocket::Core::SetSystemInterface(system_interface);

    Rocket::Core::Initialise();
    Rocket::Controls::Initialise();
    
    Rocket::Core::FontDatabase::LoadFontFace("Delicious-Bold.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Delicious-BoldItalic.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Delicious-Italic.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Delicious-Roman.otf");

   // VideoData *vd = Config::getInstance()->getVD();
    
    context = Rocket::Core::CreateContext("ui",
            Rocket::Core::Vector2i(
            renderer->getFrustum().getWidth(),
            renderer->getFrustum().getHeight())
            );

    
    ::Input::SetContext(context);
    
    Rocket::Debugger::Initialise(context);

    return true;
}

void UI::showDebug(bool show) {
    Rocket::Debugger::SetVisible(show);
}

RC::Context * UI::getContext() {
    return context;
}

UIDocument * UI::addDocument(std::string file, string name) {
    if (name == "") {
        name = file;
    }
    RC::ElementDocument *doc = context->LoadDocument(file.c_str());
    doc->RemoveReference();
    docmap[name] = new UIDocument(doc, file, name);
    return docmap[name];
}

UIDocument * UI::getDocument(string name) {
    return docmap[name];
}

void UI::processSDLEvent(SDL_Event &event) {


    switch (event.type) {
        case SDL_MOUSEMOTION:
            context->ProcessMouseMove(event.motion.x,
                    event.motion.y,
                    system_interface->GetKeyModifiers());
            break;

        case SDL_MOUSEBUTTONDOWN:
            context->ProcessMouseButtonDown(system_interface->TranslateMouseButton(event.button.button),
                    system_interface->GetKeyModifiers());
            break;

        case SDL_MOUSEBUTTONUP:
            context->ProcessMouseButtonUp(system_interface->TranslateMouseButton(event.button.button),
                    system_interface->GetKeyModifiers());
            break;

        case SDL_MOUSEWHEEL:
            context->ProcessMouseWheel(event.wheel.y, system_interface->GetKeyModifiers());
            break;

        case SDL_KEYDOWN:
            context->ProcessTextInput(::Input::GetCharacterCode(
            system_interface->TranslateKey(event.key.keysym.sym),
                    system_interface->GetKeyModifiers()
                    ));
            context->ProcessKeyDown(system_interface->TranslateKey(event.key.keysym.sym),
                    system_interface->GetKeyModifiers());

            break;
    }


}

UI::~UI() {
    context->RemoveReference();
    Rocket::Core::Shutdown();

    delete system_interface;
    delete rc_renderer_interface;
    delete file_interface;

    for (auto doc : docmap) {
        delete doc.second;
    }
}