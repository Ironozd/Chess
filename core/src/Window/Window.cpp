#include "Window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "../Renderer/Instance.h"

namespace Chess
{
    Window::Window()
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwInit();
    }

    Window::~Window()
    {
        Terminate();
    }
    
    void Window::Initialize(const WindowSpecification& spec)
    {
        m_Window = glfwCreateWindow(spec.Width, spec.Height, spec.Title.data(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
    }
    
    void Window::Terminate()
    {
        glfwDestroyWindow(m_Window);

        glfwTerminate();
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    std::vector<const char*> Window::GetExtensions()
    {
        uint32_t extensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + extensionCount);

        if(Instance::IsValidationEnabled() == true)
        {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }
}