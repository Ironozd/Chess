#include "Window.h"

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "../Renderer/Instance.h"
#include "../Core/Logger.h"

namespace Renderer
{
    Window::Window()
        : m_Window(nullptr)
    {
        // Initializes the GLFW library.
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwInit();
    }

    Window::~Window()
    {
        Terminate(); 
        /**
         * @todo re-think shutdown structure. 
         * Question: On heap allocation, would this destructor cause errors, 
         * since Shutdown can be called in other methods?
         */
    }

    void Window::Initialize(const WindowSpecification &spec)
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

    std::vector<const char *> Window::GetExtensions()
    {
        uint32_t extensionCount = 0;
        const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);

        std::vector<const char *> extensions(glfwExtensions, glfwExtensions + extensionCount);

        if (Instance::IsValidationEnabled())
        {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    void Window::CreateSurface()
    {
        VkWin32SurfaceCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        createInfo.hwnd = glfwGetWin32Window(m_Window);
        createInfo.hinstance = GetModuleHandle(nullptr);

        if (vkCreateWin32SurfaceKHR(Instance::Data(), &createInfo, nullptr, &m_Surface) != VK_SUCCESS)
        {
            LOG_ERROR("Window surface creation failed!");
            assert(false);
        }
    }

    void Window::DestroySurface()
    {
        vkDestroySurfaceKHR(Instance::Data(), m_Surface, nullptr);
    }
}