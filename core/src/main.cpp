#include "main.h"

int main(int argc, char** argv){
    Chess::Logger::Initialize();

    Chess::Engine engine;
    engine.Run();
    return 0;
}
