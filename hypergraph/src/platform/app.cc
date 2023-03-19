#include "app.h"

bool OSPlatform::init(MainArgs)
{
    gAppState = AppState(MainArgsVars);
    return true;
}

