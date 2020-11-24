#include "Rendering/Renderer.h"
#include "Input/Input.h"
#include "Input/Events.h"
#include "CyberPet.h"

#include <windows.h>
#include <iostream>
#include <vector>

void KeyboardCallback(KEY_EVENT_RECORD e)
{
    
}


int main()
{
    // initialize the renderer
    Renderer::Init();
    // create an input handling object
    Input* input = new Input;

    // set the event callback functions
    input->SetKeyEventCallback(KeyboardCallback);

    // create a new cyber pet object
    CyberPet* cyberPet = new CyberPet;

    // main loop
    bool exitLoop = false;
    while (!exitLoop)
    {
        // send the events in the event queue to their callback functions
        input->HandleEvents();
        
        // update
        cyberPet->Update();
        /*
        // clear everything from the screen
        Renderer::Clear();
        
        // add our pet to the render queue
        Renderer::Queue(cyberPet);

        // draw everything in the queue
        Renderer::DrawAll();
        */

        Sleep(30);
    }

    // program shutdown
    delete cyberPet;

    Renderer::Shutdown();
    delete input;

	return 0;
}