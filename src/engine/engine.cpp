#include "engine.hpp"
#include "resources/ResourceManager.hpp"
#include "world/WorldManager.hpp"

void Engine::pythonInit() {
    PyScripting::getInstance()->init();
    PyScripting::getInstance()->loadManipulators(); 
}

void Engine::prepare() {
    cout << "Preparing..." << endl;
    cout << "Config init..." << endl;
    
    Config::getInstance();
    LibLoad::getInstance()->discoverLoaders();

    EngineState::getInstance()->setBool("exit", false);
    EngineState::getInstance()->setBool("edit_mode", false);
    EngineState::getInstance()->setBool("debug_visual", false);
    EngineState::getInstance()->setBool("lighting", true);
    EngineState::getInstance()->setBool("noclip", false);
    EngineState::getInstance()->setBool("fullscreen", false);
    EngineState::getInstance()->setBool("desktop_fs", false);
    EngineState::getInstance()->setBool("light", false);
    EngineState::getInstance()->setBool("attach_mouse", true);
    EngineState::getInstance()->setString("version", "Staging");

    cout << "Loading world...\n";
    
    ResourceManager::getInstance()->setWD(string(CONFIG_DIR)); 
    ResourceManager::getInstance()->setLevel(Config::getInstance()->getStart());
    World *w = (World*)ResourceManager::getInstance()->get("level.xml", LEVEL);
    ResourceManager::getInstance()->resolveAllDependencies();
    WorldManager::getInstance()->setWorld(w);
  
    VideoData vd = *Config::getInstance()->getVD();

    LibLoad::getInstance()->registerModule("renderer2", "RendererOpenGL", "returnRenderer");
    RendererInterface *ri = (RendererInterface *) LibLoad::getInstance()->getModuleClass("renderer2");

    RenderingManager *rendering = RenderingManager::getInstance();

    rendering->setRenderer(ri);
    
    cout << "IO\n";
    io = new SdlIO();

    io->init(io);

    ri->init(vd.width, vd.height, io);
    rendering->setupTextures();
    rendering->setFlush(SdlIO::flush);

    string ui_dir = "./data/ui/";

    Rocket::Core::RenderInterface  *ui_renderer = ri->getUiRenderer();
    RocketSDL2SystemInterface *system_interface = new RocketSDL2SystemInterface();
    Rocket::Core::FileInterface *file_interface = new ShellFileInterface(ui_dir.c_str());
    
    UI *ui = UI::getInstance();

    if (!ui->init(system_interface, ui_renderer, file_interface, rendering->getRenderer())) {
        cout << "UI loading error" << endl;
    } else {
        cout << "UI loaded!" << endl;
    }


    this->pythonInit();
    cout << "World loop\n";

    boost::thread(boost::ref(*w));

}

Engine::~Engine() {

}

void Engine::start() {    
    boost::thread(boost::bind(&SdlIO::keyboardInputThread, SdlIO::getInstance()));
    boost::thread(boost::bind(&SdlIO::mouseInputThread, SdlIO::getInstance()));
    
    io->eventLoop();
}
