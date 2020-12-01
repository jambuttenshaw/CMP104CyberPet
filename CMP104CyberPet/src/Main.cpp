#include "Rendering/Renderer.h"
#include "Input/Input.h"
#include "GameManager.h"

#include <chrono>
// when the console window gets resized we want to update the renderer
// to store the new dimensions of the console
void WindowResizeCallback(WINDOW_BUFFER_SIZE_RECORD* e)
{
    Renderer::UpdateConsoleDimensions(e->dwSize.X, e->dwSize.Y);
}


int main()
{
    // initialize the renderer
    Renderer::Init();
    // initialize the input handler
    Input::Init();

    Input::SetEventCallback(WindowResizeCallback);


    // create a game manager
    GameManager* gameManager = new GameManager;


    // used to calculate the difference in time between this frame and the previous one: the delta time
    // this is used to make sure that everything that happens in-game is frame-rate independent
    std::chrono::high_resolution_clock::time_point lastFrameTime = std::chrono::high_resolution_clock::now();

    // main loop
    bool exitLoop = false;
    while (!exitLoop)
    {
        // get the time elapsed between this frame and the previous one
        std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(t - lastFrameTime).count() * 0.001f;
        lastFrameTime = t;

        // send the events in the event queue to their callback functions
        Input::HandleEvents();

        // update everything in the game
        gameManager->Update(deltaTime);

        
        // clear everything from the screen
        Renderer::Clear();

        // game manager draw to display
        gameManager->Draw();

        // draw everything in the queue
        Renderer::DrawAll();
        

        // check to see if we need to quit the game
        exitLoop = gameManager->TestQuitGame();


        Sleep(30);
    }

    // clear the screen one last time before quitting
    Renderer::Clear();

    delete gameManager;

    Renderer::Shutdown();
    Input::Shutdown();

	return 0;
}