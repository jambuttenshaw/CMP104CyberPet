#include "Renderer.h"

// create a new render api object
RenderAPI* Renderer::s_RenderAPI = new RenderAPI();

// initialize the render queue as an empty vector of sprite pointers
std::vector<Sprite*> Renderer::s_RenderQueue(0);
