//@Copyright (c) Drop Games Inc. 2023
//@Author: Timofej Jermolaev
/*@File provided as is, under MIT license
<Summary>
Windows-specific header files
</Summary>
*/

#pragma once

#include <Windows.h>
// #include "../platform/input.h"
#include "../window.h"

#include <queue>
#include <functional>

namespace OSPlatform
{
    class EventQueue
    {
        public:
           void update();
    };

    class Window
    {
    public:
        // Initialize this window with the Win32 API.
        bool create(const WindowSettings &desc, EventQueue &eventQueue);

        void close();
    };
}