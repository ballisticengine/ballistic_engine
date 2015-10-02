#include <gtest/gtest.h>

#include "renderer/RenderingManager.hpp"
#include "renderer/RendererInterface.hpp"
#include "libload/LibLoad.hpp"
#include "io/sdlio.hpp"
#include "types/Vector3d.hpp"

TEST(RendererInterface, RendererInterfaceTest) {
    LibLoad::getInstance()->setWD("./bin");
    RenderingManager *rendering = RenderingManager::getInstance();
    LibLoad::getInstance()->registerModule("renderer2", "RendererOpenGL", "returnRenderer");
    RendererInterface *ri = (RendererInterface *) LibLoad::getInstance()->getModuleClass("renderer2");
    rendering->setRenderer(ri);

    SdlIO *io = new SdlIO();
    io->init(io);
    ri->init(800, 600, io);
    rendering->getRenderer()->unproject(10, 10);
    rendering->getRenderer()->unproject(0, 0);
    rendering->getRenderer()->unproject(1, 1);

}