#include "Rendering/Renderer.h"
#include "CyberPet.h"

int main()
{
    // project set up
    Renderer::Init();

    CyberPet* cyberPet = new CyberPet;

    // main loop
    bool exitLoop = false;
    while (!exitLoop)
    {
        // update
        cyberPet->Update();

        // redraw to the display
        Renderer::Clear();
    }

    // program shutdown
    delete cyberPet;
    Renderer::Shutdown();

	return 0;
}