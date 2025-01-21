#include "Renderer.h"

#include "Instance.h"

namespace Chess
{
//    Instance Renderer::m_Instance;

    Renderer::Renderer(const RendererSpecification& spec)
    {
        
    }

    Renderer::~Renderer()
    {
    }

    void Renderer::Initialize()
    {
        InstanceSpecification instanceSpec{};
        instanceSpec.ApplicationName = "Chess";
        instanceSpec.EngineName = "Chess Display Engine";

        Instance::Initialize(instanceSpec);
    }

    void Renderer::Shutdown()
    {
        Instance::Shutdown();
    }
}