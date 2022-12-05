#include "appframework/app.h"

int main(int argc, const char *argv[])
{
    AppFramework::init(argc, argv);
    AppFramework::gAppMain(argc, argv);
}


