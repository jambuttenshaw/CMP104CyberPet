#include "Renderer.h"

#include <codecvt>

RenderAPI* Renderer::s_RenderAPI = new RenderAPI();
std::vector<Sprite*> Renderer::s_RenderQueue(0);
