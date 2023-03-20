//@Copyright (c) Drop Games Inc. 2023
//@Author: Timofej Jermolaev
/*@File provided as is, under MIT license
<Summary>
This file represents the application layer over common operating systems,
including: windows @todo: linux, osx, iosx, android, LG smart fridge?
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


namespace OSPlatform
{
    struct OSPlatformState
    {
#ifdef PLATFORM_WIN32
        HINSTANCE hInstance;
        HINSTANCE hPrevInstance;
        LPSTR lpCmdLine;
        int nCmdShow;

        OSPlatformState(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
                  int nCmdShow)
            : hInstance(hInstance), hPrevInstance(hPrevInstance),
              lpCmdLine(lpCmdLine), nCmdShow(nCmdShow)
        {


        }
#else
    int argc;
    const char** argv;
    OSPlatformState(int argc, const char* argv[]) : argc(argc), argv(argv) {}

#endif
        OSPlatformState(){}
    };

    
    bool init(MainArgs);

    const OSPlatformState& getGlobalAppState();
}

