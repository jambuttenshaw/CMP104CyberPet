#include "Rendering/Renderer.h"
#include "CyberPet.h"

#include <windows.h>
#include <vector>

int main()
{
    // initialize the renderer
    Renderer::Init();

    // create a new cyber pet object
    CyberPet* cyberPet = new CyberPet;

    // ABSTRACT THE DRAW QUEUE
    std::vector<Sprite*> sprites;
    sprites.push_back(cyberPet);

    // main loop
    bool exitLoop = false;
    while (!exitLoop)
    {
        // update
        cyberPet->Update();

        // redraw to the display
        
        Renderer::Clear();
        for (Sprite* s : sprites)
        {
            if (s->IsDirty())
            {
                Renderer::Submit(s);
                s->Clean();
            }
        }

        Sleep(30);
    }

    // program shutdown
    delete cyberPet;
    Renderer::Shutdown();

	return 0;
}