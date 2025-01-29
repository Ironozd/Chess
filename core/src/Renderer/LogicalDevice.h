#pragma once

/* Forward declaration for better compile-time and organization */
typedef struct VkDevice_T *VkDevice;
typedef struct VkQueue_T *VkQueue;

namespace Chess
{
    /**
     * @brief Logical Device singleton.
     *
     * @note Since Vulkan VkDevice (LogicalDevice) is expected to be created and destroyed once
     * and Queues that are going to be accessed throughoutare created depending on this class, 
     * this class was made a singleton.
     * @note This device can be created more than once, however, for the current use case, singleton
     * appeared to be the better fit.
     */
    class LogicalDevice
    {
    public:
        static void Create() { Get().CreateImpl(); }
        static void Shutdown() { Get().ShutdownImpl(); }

    private: /* Private variables */
        VkDevice m_LogicalDevice;
        VkQueue m_GraphicsQueue;
        VkQueue m_PresentQueue;

    private: /* Singleton functionality */
        static LogicalDevice &Get()
        {
            static LogicalDevice device;
            return device;
        }

        LogicalDevice();
        ~LogicalDevice();

    private: /* Implementations */
        void CreateImpl();
        void ShutdownImpl();
    };
}