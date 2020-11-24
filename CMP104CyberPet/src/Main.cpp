#include "Rendering/Renderer.h"
#include "Input/Input.h"
#include "Input/Events.h"
#include "CyberPet.h"

#include <windows.h>
#include <iostream>
#include <vector>

void OnKeyboardEvent(INPUT_RECORD e)
{
    KEY_EVENT_RECORD keyEvent = e.Event.KeyEvent;
    bool pressEvent = keyEvent.bKeyDown;
    char key = keyEvent.uChar.AsciiChar;

}

int main()
{
    // initialize the renderer
    Renderer::Init();
    // create an input handling object
    Input* input = new Input;

    // create a new cyber pet object
    CyberPet* cyberPet = new CyberPet;

    // main loop
    bool exitLoop = false;
    while (!exitLoop)
    {
        // poll the event queue
        intptr_t queueEnd = (intptr_t)input->GetEventQueueStart() + input->PollEvents();
        for (INPUT_RECORD* e = input->GetEventQueueStart(); (intptr_t)e < queueEnd; e++)
        {
            EventDispatcher dispatcher(*e);
            dispatcher.Dispatch(KEY_EVENT, OnKeyboardEvent);
        }
        
        // update
        cyberPet->Update();

        // clear everything from the screen
        Renderer::Clear();
        
        // add our pet to the render queue
        Renderer::Queue(cyberPet);

        // draw everything in the queue
        Renderer::DrawAll();


        Sleep(30);
    }

    // program shutdown
    delete cyberPet;

    Renderer::Shutdown();
    delete input;

	return 0;
}