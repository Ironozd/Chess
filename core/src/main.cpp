#include "main.h"

int main(int argc, char **argv)
{
    Chess::Logger::Initialize(); // Logger is seperate from the Engine.

    Chess::Engine engine;
    engine.Run();

    return 0;
}
