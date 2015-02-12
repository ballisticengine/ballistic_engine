#include "engine.hpp"

void engine::pythonInit() {
    PyScripting::getInstance()->loadManipulators();

}

void engine::preview(string model) {
    cout << "Model: " << model << endl;
    cout << "Preparing..." << endl;

    cout << "Config init..." << endl;
    config::getInstance();
    
    GLPreview *pr = new GLPreview();

    cout << "IO\n";


    io = new sdlIO();
    return;
    io->initWindow(io);
    io->setRenderer(pr);
//    cout << "Renderer init\n";
    //shapeFactory::getInstance()->setWD(".");
    shape *s=(shape *)shapeFactory::getInstance()->get(model);
    pr->setModel(s);
    pr->previewInit();
    pr->setFlush(sdlIO::flush);
    io->previewLoop();
    
}

void engine::prepare() {
    cout << "Preparing..." << endl;

    cout << "Config init..." << endl;
    config::getInstance();

    cout << "Get World\n";
    world *w = (world *) world::getInstance();
    string start_lvl_dir = string(CONFIG_DIR) + string(DS) + string(LVL_DIR),
            start_lvl = start_lvl_dir + DS + config::getInstance()->getStart();
    cout << start_lvl << endl;
    w->parseXml(config::getInstance()->getStart());

    videoData vd = *config::getInstance()->getVD();



    r = RendererGL::getInstance();

    cout << "IO\n";


    io = new sdlIO();

    io->initWindow(io);
    io->setRenderer(r);
    cout << "Renderer init\n";
    r->init();
    cout << "Camera set\n";
    r->setCamera(w->getCurrentCamera());
    cout << "Flush set\n";
    r->setFlush(sdlIO::flush);
    // boost::thread(boost::ref(*r));
    this->pythonInit();
    cout << "World loop\n";
    boost::thread(boost::ref(*w));






}

engine::~engine() {

}

void engine::start() {

    io->eventLoop();


}
