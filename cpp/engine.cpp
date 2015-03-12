#include "engine.hpp"

void Engine::pythonInit() {
    PyScripting::getInstance()->loadManipulators();

}

void Engine::preview(string model) {
//    cout << "Model: " << model << endl;
//    cout << "Preparing..." << endl;
//
//    cout << "Config init..." << endl;
//    Config::getInstance();
//    
//    GLPreview *pr = new GLPreview();
//
//    cout << "IO\n";
//
//
//    io = new SdlIO();
//    return;
//    io->initWindow(io);
//    io->setRenderer(pr);
////    cout << "Renderer init\n";
//    //shapeFactory::getInstance()->setWD(".");
//    Shape *s=(Shape *)ShapeFactory::getInstance()->get(model);
//    pr->setModel(s);
//    pr->previewInit();
//    pr->setFlush(SdlIO::flush);
//    io->previewLoop();
//    
}

void Engine::prepare() {
    cout << "Preparing..." << endl;

    cout << "Config init..." << endl;
    Config::getInstance();
    
    cout << "Get World\n";
    World *w = (World *) World::getInstance();
    string start_lvl_dir = string(CONFIG_DIR) + string(DS) + string(LVL_DIR),
            start_lvl = start_lvl_dir + DS + Config::getInstance()->getStart();
    cout << start_lvl << endl;
    w->parseXml(Config::getInstance()->getStart());

    VideoData vd = *Config::getInstance()->getVD();

    cout << "renderer is: " << Config::getInstance()->getRenderer() << endl;

    r = LibLoad::getInstance()->getRenderer(Config::getInstance()->getRenderer());//RendererGL::getInstance();
    
    cout << "IO\n";


    io = new SdlIO();

    io->initWindow(io);
    io->setRenderer(r);
    cout << "Renderer init\n";
    r->init();
    cout << "Camera set\n";
    r->setCamera(w->getCurrentCamera());
    cout << "Flush set\n";
    r->setFlush(SdlIO::flush);
    // boost::thread(boost::ref(*r));
    this->pythonInit();
    cout << "World loop\n";
    boost::thread(boost::ref(*w));






}

Engine::~Engine() {

}

void Engine::start() {

    io->eventLoop();


}
