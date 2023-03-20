

void appMain(int argc, const char** argv)
{
    OSPlatform::WindowSettings windowDesc;
    windowDesc.name = "Test";
    windowDesc.title = "My Title";
    windowDesc.visible = true;
    windowDesc.width = 1280;
    windowDesc.height = 720;

    bool closed = false;
    OSPlatform::Window window;
    OSPlatform::EventQueue inputEventQueue;

    if (!window.create(windowDesc, inputEventQueue))
    {
        return;
    }

    bool isRunning = true;

    while (isRunning)
    {
        inputEventQueue.update();
    }
}


typedef void (*AppMainFnPtr)(int argc, const char** argv);
AppMainFnPtr gAppMain = appMain;

