#include "ui/UIDocument.hpp"

UIDocument::UIDocument(RC::ElementDocument *document, string file_name, string name)
: document(document), file_name(file_name), name(name) {
}

void UIDocument::getElements(string selector, ElementList & elements) {

    if (selector[0] == '.') {
        string cname = selector.substr(1);
        document->GetElementsByClassName(elements, cname.c_str());
        cout << "CNAME" << cname << endl;
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

void UIDocument::addEventListener(string id, string event, string signal) {

    ElementList elements;
    getElements(id, elements);

    for (auto el : elements) {
        SignalListener *listen = new SignalListener(signal);
        el->AddEventListener(event.c_str(), listen, false);
    }
}

void UIDocument::show() {
    document->Show();
}

void UIDocument::hide() {
    document->Hide();
}
