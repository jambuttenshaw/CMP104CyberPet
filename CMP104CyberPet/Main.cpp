#include "Renderer.h"

int main()
{
    // project set up
    Renderer::Init();

    // main loop
    bool exitLoop = false;
    while (!exitLoop)
    {
        // update

        // redraw to the display
        Renderer::Clear();
    }

    // program shutdown
    Renderer::Shutdown();

	return 0;
}