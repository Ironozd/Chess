#include "Engine.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Logger.h"


namespace Chess
{
    Engine::Engine()
    : m_Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"), 
    m_Window(), m_Renderer({})
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
        m_Running = false;
    }
}