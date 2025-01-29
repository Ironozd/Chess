#include "PhysicalDevice.h"

#include <vulkan/vulkan.h>

#include "Instance.h"

#include "../Core/Logger.h"
#include "../Window/Window.h"

namespace Chess
{
    PhysicalDevice::PhysicalDevice() : 
        m_PhysicalDevice(VK_NULL_HANDLE), m_Specification({nullptr})
    {
    }

    void PhysicalDevice::PickImpl(const PhysicalDeviceSpecification &spec)
    {
        m_Specification = spec;
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(Instance::Data(), &deviceCount, nullptr);

        if (deviceCount == 0)
        {
            LOG_ERROR("No GPU with Vulkan support found!");
            assert(false);
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(Instance::Data(), &deviceCount, devices.data());

        for (const auto &device : devices)
        {
            if (IsDeviceSuitable(device))
            {
                m_PhysicalDevice = device;
                break;
            }
        }

        if (m_PhysicalDevice == VK_NULL_HANDLE)
        {
            LOG_ERROR("No suitable GPU found!");
            assert(false);
        }
    }

    bool PhysicalDevice::IsDeviceSuitable(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices = FindQueueFamilies(device);

        return indices.IsComplete();
    }

    QueueFamilyIndices PhysicalDevice::FindQueueFamilies(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices;
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto &queueFamily : queueFamilies)
        {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                indices.GraphicsFamily = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_Specification.WindowRef->SurfaceData(), &presentSupport);

            if (presentSupport)
            {
                indices.PresentFamily = i;
            }

            if (indices.IsComplete())
            {
                break;
            }

            i++;
        }
        return indices;
    }
}