#pragma once

#include "../ChessLogic/Board.h"
#include "../Window/Window.h"
#include "../Renderer/Renderer.h"

namespace Chess{
    class Engine
    {
    public:
        Engine();
        ~Engine();

        void Run();

        void Shutdown();
    private:
        Board m_Board;
        Window m_Window;
        Renderer m_Renderer;

        bool m_Running = true;
    };
}