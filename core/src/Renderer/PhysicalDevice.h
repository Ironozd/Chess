#pragma once

#include <optional>

/* Forward declaration for better compile-time and organization */
typedef struct VkPhysicalDevice_T *VkPhysicalDevice;

namespace Chess
{
    /* Forward declaration for better compile-time and organization */
    class Window;

    struct PhysicalDeviceSpecification
    {
        Window *WindowRef = nullptr;
    };
    /**
     * @brief Duplicate as in the one in Vulkan Tutorial.
     */
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> GraphicsFamily;
        std::optional<uint32_t> PresentFamily;

        bool IsComplete()
        {
            return GraphicsFamily.has_value() && PresentFamily.has_value();
        }
    };
    /**
     * @brief Physical Device singleton.
     *
     * @note Since Vulkan VkDevice (PhysicalDevice) is expected to be picked once
     * and QueuesFamilies are created depending on this class, this class was made a singleton.
     */
    class PhysicalDevice
    {
    public:
        static void Pick(const PhysicalDeviceSpecification &spec) { Get().PickImpl(spec); }

        static VkPhysicalDevice Data() { return Get().m_PhysicalDevice; }

        static QueueFamilyIndices GetFamilyIndices() { return Get().FindQueueFamilies(Get().m_PhysicalDevice); }

    private:
        VkPhysicalDevice m_PhysicalDevice;
        PhysicalDeviceSpecification m_Specification;

    private: /* Singleton functionality */
        static PhysicalDevice &Get()
        {
            static PhysicalDevice device;
            return device;
        }

        PhysicalDevice();

    private: /* Implementations */
        void PickImpl(const PhysicalDeviceSpecification &spec);

    private: /* Private functions */
        /**
         * @brief Checks physical device for the required properties.
         * 
         * @param VkPhysicalDevice device : Physical device to be checked. 
         * @return true : suitable
         * @return false : not suitable
         */
        bool IsDeviceSuitable(VkPhysicalDevice device);
        /**
         * @brief Returns QueueFamilyIndices for given VkPhysicalDevice
         * 
         * @param VkPhysicalDevice device : Physical device to be accessed.  
         * @return QueueFamilyIndices : Queues to submit processing information.
         */
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    };
}