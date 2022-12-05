#pragma once

#ifdef PLATFORM_WIN32 
#include <windows.h>
#define MainArgs                                                               \
    HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
#define MainArgsVars hInstance, hPrevInstance, lpCmdLine, nCmdShow
#else 
#define MainArgs int argc, const char *argv[]
#define MainArgsVars argc, argv
#endif

typedef void AppMainFnPtr(int argc, const char** argv);
AppMainFnPtr gAppMain;

namespace AppFramework
{
    struct AppState
    {

#ifdef PLATFORM_WIN32
        HINSTANCE hInstance;
        HINSTANCE hPrevInstance;
        LPSTR lpCmdLine;
        int nCmdShow;

        AppState(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
                  int nCmdShow)
            : hInstance(hInstance), hPrevInstance(hPrevInstance),
              lpCmdLine(lpCmdLine), nCmdShow(nCmdShow)
        {
        }
#else
    int argc;
    const char** argv;
    AppState(int argc, const char* argv[]) : argc(argc), argv(argv) {}
#endif
        AppState(){}
    };

    static AppState gAppState;
    

    bool init( MainArgs);
   
}

