#include "Renderer.h"

#include "Instance.h"
#include "LogicalDevice.h"
#include "DebugMessenger.h"
#include "PhysicalDevice.h"

#include "../Window/Window.h"

namespace Chess
{
    Renderer::Renderer(const RendererSpecification& spec) :
        m_Specification(spec)
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
        DebugMessenger::Implement();
        m_Specification.WindowRef.CreateSurface();

        PhysicalDeviceSpecification physicalDeviceSpec{nullptr};
        physicalDeviceSpec.WindowRef = &m_Specification.WindowRef;
        PhysicalDevice::Pick(physicalDeviceSpec);
        LogicalDevice::Create();
    }

    void Renderer::Shutdown()
    {
        LogicalDevice::Shutdown();
        DebugMessenger::Destroy();
        m_Specification.WindowRef.DestroySurface();
        Instance::Shutdown();
    }
}