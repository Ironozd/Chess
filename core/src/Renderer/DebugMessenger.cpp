#include "DebugMessenger.h"

#include <vulkan/vulkan.h>

#include "Instance.h"
#include "../Core/Logger.h"

namespace Chess
{
    VkDebugUtilsMessengerEXT DebugMessenger::m_DebugMessenger = nullptr;

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
        void *pUserData)
    {
        LOG_ERROR("Vulkan Validation Layer: {0}", pCallbackData->pMessage);

        return VK_FALSE;
    }
    
    void DebugMessenger::Implement()
    {
        if (!Instance::IsValidationEnabled())
            return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        populateInfo(createInfo);

        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(Instance::Data(), "vkCreateDebugUtilsMessengerEXT");

        if (func == nullptr)
        {
            LOG_ERROR("Could not find vkCreateDebugUtilsMessengerEXT");
            assert(false);
        }

        if (func(Instance::Data(), &createInfo, nullptr, &m_DebugMessenger) != VK_SUCCESS)
        {
            LOG_ERROR("Failed to set up debug messenger!");
            assert(false);
        }
    }
    
    void DebugMessenger::Destroy()
    {
        if (!Instance::IsValidationEnabled())
            return;

        auto destroy = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(Instance::Data(), "vkDestroyDebugUtilsMessengerEXT");

        if (destroy == nullptr)
        {
            LOG_ERROR("Could not find vkDestroyDebugUtilsMessengerEXT");
            assert(false);
        }

        destroy(Instance::Data(), m_DebugMessenger, nullptr);
    }

    void DebugMessenger::populateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo)
    {
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr;
    }
}