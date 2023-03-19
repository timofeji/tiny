//@Copyright (c) Drop Games Inc. 2023
//@Author: Timofej Jermolaev
/*@File provided as is, under MIT license
<Summary>
This file represents the application layer over many operating systems,
including: windows
@todo: linux, osx, iosx, android, LG smart fridge?
</Summary>
*/
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

// typedef void AppMainFnPtr(MainArgsVars);
// AppMainFnPtr gAppMain;

namespace OSPlatform
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
    
    bool init(MainArgs);
}

