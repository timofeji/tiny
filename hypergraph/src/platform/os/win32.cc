//@Copyright Drop Games Inc. 2023
/*
<Summary>
Windows specific app entry
</Summary>
*/
#include <windowsx.h>
#ifndef UNICODE
#define UNICODE
#endif 

#include "win32.h"
#include "../app.h"
#include "../main.h"


LPSTR lpCmdLine;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
// #ifdef _DEBUG
//     AllocConsole();
//     FILE* pCout;
//     FILE* pCerr;
//     freopen_s(&pCout, "CONOUT$", "w+", stdout);
//     freopen_s(&pCerr, "CONOUT$", "w+", stderr);
// #endif
    //setup cmdline
    MSG msg;    // message
    int argc;
    char **argv;

    // Ensure wParam is initialized.
    msg.wParam = 0;

    // Use the CommandLine functions to get the command line arguments.
    // Unfortunately, Microsoft outputs
    // this information as wide characters for Unicode, and we simply want the
    // Ascii version to be compatible
    // with the non-Windows side.  So, we have to convert the information to
    // Ascii character strings.
    LPWSTR *commandLineArgs = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (NULL == commandLineArgs) {
        argc = 0;
    }

    if (argc > 0) {
        argv = (char **)malloc(sizeof(char *) * argc);
        if (argv == NULL) {
            argc = 0;
        } else {
            for (int iii = 0; iii < argc; iii++) {
                size_t wideCharLen = wcslen(commandLineArgs[iii]);
                size_t numConverted = 0;

                argv[iii] = (char *)malloc(sizeof(char) * (wideCharLen + 1));
                if (argv[iii] != NULL) {
                    wcstombs_s(&numConverted, argv[iii], wideCharLen + 1, commandLineArgs[iii], wideCharLen + 1);
                }
            }
        }
    } else {
        argv = NULL;
    }

    // Initialize our application and call application main
    OSPlatform::init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
    if (gAppMain)
    {
        gAppMain(argc, (const char **)argv);
    }

    // Free up the items we had to allocate for the command line arguments.
    if (argc > 0 && argv != NULL) {
        for (int iii = 0; iii < argc; iii++) {
            if (argv[iii] != NULL) {
                free(argv[iii]);
            }
        }
        free(argv);
    }

    return msg.wParam;
}


/// WINDOW
namespace OSPlatform
{
    bool Window::create(const WindowSettings &desc, EventQueue &eventQueue)
    {
        const wchar_t CLASS_NAME[]  = L"Sample Window Class";
        const wchar_t TITLE_NAME[]  = L"Sample Window Class";

        const OSPlatform::OSPlatformState& state = getGlobalAppState();

        HINSTANCE hInstance = state.hInstance;
        WNDCLASS wc = {};
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = CLASS_NAME;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.lpszMenuName = NULL;
        wc.hbrBackground = (HBRUSH)(COLOR_3DHILIGHT+1);

        RegisterClass(&wc);

        HWND hWnd = CreateWindowEx(
            0,                           // Optional window styles.
            CLASS_NAME,                  // Window class
            L"Learn to Program Windows", // Window text
            WS_OVERLAPPEDWINDOW,         // Window style

            // Size and position
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

            NULL,      // Parent window
            NULL,      // Menu
            hInstance, // Instance handle
            NULL       // Additional application data
        );

        if (hWnd == NULL)
        {
            return 0;
        }

        ShowWindow(hWnd, state.nCmdShow);
        SetForegroundWindow(hWnd);

        return true;
    }

    void Window::close()
    {
        
    }

    void EventQueue::update()
    {
        MSG msg = {};

        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // Translate virtual key messages
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch (message)
    {
    // this message is read when the window is closed
    case WM_DESTROY:
    {
        // close the application entirely
        PostQuitMessage(0);
        return 0;
    }
    break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc(hWnd, message, wParam, lParam);
}