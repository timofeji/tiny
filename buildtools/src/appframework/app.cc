#include "app.h"

bool AppFramework::init( MainArgs)
{
    gAppState = AppState(MainArgsVars);
    return true;
}

