#include "Rendering/Renderer.h"
#include "CyberPet.h"

#include <iostream>

int main()
{
    // initialize the renderer
    Renderer::Init();

    // create a new cyber pet object
    CyberPet* cyberPet = new CyberPet;

    // main loop
    bool exitLoop = false;
    while (!exitLoop)
    {
        // update
        cyberPet->Update();

        // redraw to the display
        Renderer::Submit(cyberPet->GetImage(), { 5, 4 });
    }

    // program shutdown
    delete cyberPet;
    Renderer::Shutdown();

	return 0;
}