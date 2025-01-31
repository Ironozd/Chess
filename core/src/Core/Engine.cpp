#include "Engine.h"

#include "Logger.h"


namespace Chess
{
    Engine::Engine()
    : m_Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"), // Start FEN String
    m_Window(), m_Renderer({m_Window})
    {
        WindowSpecification spec{};
        spec.Title = "Chess";
        spec.Width = 800;
        spec.Height = 600;
        m_Window.Initialize(spec);

        m_Renderer.Initialize();
    }

    Engine::~Engine()
    {
        Shutdown();
    }
    
    void Engine::Run()
    {
        while(m_Running)
        {
            
            m_Window.OnUpdate();
        }
    }
    
    void Engine::Shutdown()
    {
        m_Renderer.Shutdown();
        m_Running = false;
    }
}