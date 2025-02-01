#include "LogicalDevice.h"

#include <vulkan/vulkan.h>

#include "../Core/Logger.h"
#include "PhysicalDevice.h"
#include "Instance.h"
#include <set>

namespace Renderer
{
    LogicalDevice::LogicalDevice() : m_LogicalDevice(VK_NULL_HANDLE), m_GraphicsQueue(VK_NULL_HANDLE)
    {
    }

    LogicalDevice::~LogicalDevice()
    {
    }

    void LogicalDevice::CreateImpl()
    {
        QueueFamilyIndices indices = PhysicalDevice::GetFamilyIndices();

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.GraphicsFamily.value(), indices.PresentFamily.value()};

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = 0;

        std::vector<const char *> validationLayers = Instance::GetValidationLayers();

        if (Instance::IsValidationEnabled())
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(PhysicalDevice::Data(), &createInfo, nullptr, &m_LogicalDevice) != VK_SUCCESS)
        {
            LOG_ERROR("Logical device creation failed!");
            assert(false);
        }

        vkGetDeviceQueue(m_LogicalDevice, indices.GraphicsFamily.value(), 0, &m_GraphicsQueue);
        vkGetDeviceQueue(m_LogicalDevice, indices.PresentFamily.value(), 0, &m_PresentQueue);
    }

    void LogicalDevice::ShutdownImpl()
    {
        vkDestroyDevice(m_LogicalDevice, nullptr);
    }
}