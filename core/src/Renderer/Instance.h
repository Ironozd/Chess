#pragma once
#include <string_view>
#include <vector>

/* Forward declaration for better compile-time and organization */
typedef struct VkInstance_T *VkInstance;
struct VkApplicationInfo;

namespace Renderer
{
    struct InstanceSpecification
    {
        std::string_view ApplicationName;
        std::string_view EngineName;
    };
    /**
     * @brief Instance singleton.
     * 
     * @note Since Vulkan instance is expected to be created and destroyed once, this class was made a singleton.
     */
    class Instance
    {
    public:
        static void Initialize(const InstanceSpecification &spec) { Get().InitializeImpl(spec); }

        static void Shutdown() { Get().ShutdownImpl(); }

        /**
         * @brief Getter for private static variable validationEnabled.
         */
        static bool IsValidationEnabled() { return validationEnabled; }
        /**
         * @brief Getter for private static variable validationLayers.
         */
        static std::vector<const char*> GetValidationLayers() { return validationLayers; }

        static VkInstance Data() { return Get().m_Instance; }
    private: /* Private variables*/
        VkInstance m_Instance;
    private: /* Below variables should be accessible before instance creation of singleton, therefore, static and private */
        static bool validationEnabled;
        static std::vector<const char *> validationLayers;
    private: /* Singleton functionality */
        Instance();
        ~Instance();

        static Instance &Get()
        {
            static Instance instance;
            return instance;
        }

    private: /* Implementations */
        void InitializeImpl(const InstanceSpecification &spec);
        void ShutdownImpl();

    private: /* Private functions */
        void CreateInstance(const VkApplicationInfo &appInfo);
        bool ValidationExists();
    };

}