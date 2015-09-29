#include "ui/UIDocument.hpp"

UIDocument::UIDocument(RC::ElementDocument *document, string file_name, string name)
: document(document), file_name(file_name), name(name) {
}

UIDocument::~UIDocument() {
    for(auto l: listeners) {
        delete l;
    }
}

void UIDocument::getElements(string selector, ElementList & elements) {

    if (selector[0] == '.') {
        document->GetElementsByClassName(elements, selector.substr(1).c_str());
    } else if (selector[0] == '#') {
        RC::Element *el = document->GetElementById(selector.substr(1).c_str());
        elements.push_back(el);
    } else {
        document->GetElementsByTagName(elements, selector.c_str());
    }
}

void UIDocument::setContent(string id, string content) {
    ElementList elements;
    getElements(id, elements);
    for (auto el : elements) {
        el->SetInnerRML(content.c_str());
    }
}

RC::ElementDocument * UIDocument::getDocument() {
    return this->document;
}

void UIDocument::addEventListener(string id, string event, string signal) {

    ElementList elements;
    getElements(id, elements);
    SignalListener *listen;
    if (event == "submit") {
        listen = new FormSignalListener(signal);
    } else {
        listen = new SignalListener(signal);
    }
    
    listeners.push_back(listen);
    for (auto el : elements) {
        
        el->AddEventListener(event.c_str(), listen, false);
    }
}

void UIDocument::show() {
    document->Show();
}

void UIDocument::hide() {
    document->Hide();
}
