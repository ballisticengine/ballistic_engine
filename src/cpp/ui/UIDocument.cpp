#include "ui/UIDocument.hpp"

UIDocument::UIDocument(RC::ElementDocument *document, string file_name, string name)
: document(document), file_name(file_name), name(name) {
   

    
}

void UIDocument::setContentByID(string id, string content) {
    Rocket::Core::Element * el = Rocket::Core::ElementUtilities::GetElementById(document, id.c_str());
    el->SetInnerRML(content.c_str());
}

void UIDocument::addEventListenerID(string id, string event, string signal) {
    Rocket::Core::Element * el = document->GetElementById(id.c_str());
             //Rocket::Core::ElementUtilities::GetElementById(context->GetFocusElement(), id.c_str());
     SignalListener *listen = new SignalListener(signal);
     el->AddEventListener(event.c_str(), listen, false);
}

void UIDocument::show() {
    document->Show();
}

void UIDocument::hide() {
    document->Hide();
}
