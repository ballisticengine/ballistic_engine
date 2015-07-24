#include "renderer/RenderingManager.hpp"

void RenderingManager::setFlush(flush_function flush_callback) {
    this->flush_callback = flush_callback;
}

void RenderingManager::init() {

}

void RenderingManager::render() {
    this->flush_callback();
}

RenderingManager::RenderingManager() {

}

RenderingManager::~RenderingManager() {

}

void RenderingManager::setRenderer(RendererInterface *renderer) {
    this->renderer=renderer;
}