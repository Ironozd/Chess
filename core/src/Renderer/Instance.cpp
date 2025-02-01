#include "Instance.h"

#include <vulkan/vulkan.h>

#include "../Window/Window.h"
#include "../Core/Logger.h"
#include "DebugMessenger.h"

namespace Renderer
{
    std::vector<const char *> Instance::validationLayers = {
        "VK_LAYER_KHRONOS_validation"};
        
    bool Instance::validationEnabled = true;

    Instance::Instance() :
        m_Instance(VK_NULL_HANDLE)
    {
    }

    Instance::~Instance()
    {
        ShutdownImpl(); /** @todo Check here. */
    }

    void Instance::InitializeImpl(const InstanceSpecification &spec)
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = spec.ApplicationName.data();
        appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
        appInfo.pEngineName = spec.EngineName.data();
        appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        CreateInstance(appInfo);
    }

    void Instance::ShutdownImpl()
    {
        vkDestroyInstance(m_Instance, nullptr);
    }

    void Instance::CreateInstance(const VkApplicationInfo &appInfo)
    {
        if (validationEnabled && !(ValidationExists()))
        {
            LOG_ERROR("Validation layers not available");
            assert(false);
        }
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        std::vector<const char *> extensions = Window::GetExtensions();

        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        if (validationEnabled == true)
        {
            createInfo.enabledLayerCount = 1;
            createInfo.ppEnabledLayerNames = validationLayers.data();

            VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
            DebugMessenger::populateInfo(debugCreateInfo);

            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        }
        else
        {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        VkResult result = vkCreateInstance(&createInfo, nullptr, &m_Instance);

        if (result != VK_SUCCESS)
        {
            LOG_ERROR("Instance creation failed.");
            assert(false);
        }
    }

    bool Instance::ValidationExists()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char *layerName : validationLayers)
        {
            bool found = false;

            for (const auto &layerProperties : availableLayers)
            {
                if (strcmp(layerProperties.layerName, layerName) == 0)
                {
                    found = true;
                    break;
                }
            }

            if (found == false)
            {
                return false;
            }
        }

        return true;
    }
}