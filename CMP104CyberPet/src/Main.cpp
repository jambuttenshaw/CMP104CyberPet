#include "Rendering/Renderer.h"
#include "Input/Input.h"
#include "CyberPet.h"

#include <windows.h>
#include <iostream>
#include <vector>

int main()
{
    // initialize the renderer
    Renderer::Init();
    // create an input handling object
    Input* input = new Input;

    // create a new cyber pet object
    CyberPet* cyberPet = new CyberPet;

    // ABSTRACT THE DRAW QUEUE
    std::vector<Sprite*> sprites;
    sprites.push_back(cyberPet);
       

    // main loop
    bool exitLoop = false;
    while (!exitLoop)
    {
        // poll the event queue
        int queueEnd = (int)input->GetEventQueueStart() + input->PollEvents();
        for (INPUT_RECORD* e = input->GetEventQueueStart(); (int)e < queueEnd; e++)
        {
            // handle the event e
            switch (e->EventType)
            {
            case KEY_EVENT:
                std::cout << "Key event" << std::endl;
                break;
            }
        }

        // update
        cyberPet->Update();

        // redraw to the display
        
        /*
        Renderer::Clear();
        for (Sprite* s : sprites)
        {
            if (s->IsDirty())
            {
                Renderer::Submit(s);
                s->Clean();
            }
        }
        */

        Sleep(30);
    }

    // program shutdown
    delete cyberPet;

    Renderer::Shutdown();
    delete input;

	return 0;
}