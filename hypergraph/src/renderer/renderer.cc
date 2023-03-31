#include "renderer.h"
#include "backend.h"


void Renderer::init()
{
    RendererBackend backend;
    backend.init();
}
