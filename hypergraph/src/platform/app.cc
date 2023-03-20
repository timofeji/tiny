#include "app.h"

namespace OSPlatform
{
    namespace{

        OSPlatformState gPlatformState;
    }
    bool init(MainArgs)
    {
        gPlatformState = OSPlatformState(MainArgsVars);
        return true;
    }

    const OSPlatformState& OSPlatform::getGlobalAppState() { return gPlatformState; }
}