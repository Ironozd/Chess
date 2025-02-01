#pragma once

/* Forward declaration for better compile-time and organization */
typedef struct VkDebugUtilsMessengerEXT_T *VkDebugUtilsMessengerEXT;
struct VkDebugUtilsMessengerCreateInfoEXT;

namespace Renderer
{
    /**
     * @brief Vulkan Debug Messenger class.
     */
    class DebugMessenger
    {
    public:
        static void Implement();
        static void Destroy();

        /**
         * @brief Populates Create Specification layout for Debug Messenger.
         *
         * @param VkDebugUtilsMessengerCreateInfoEXT& createInfo : Outputs to this parameter.
         * @note As stated in Vulkan Tutorial, this function exists to prevent duplicate code.
         */
        static void populateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

    private:
        static VkDebugUtilsMessengerEXT m_DebugMessenger;
    };

}