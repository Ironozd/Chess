#pragma once
#include <string_view>
#include <vector>

typedef struct VkInstance_T *VkInstance; // Forward decl
struct VkApplicationInfo;

namespace Chess
{
    struct InstanceSpecification
    {
        std::string_view ApplicationName;
        std::string_view EngineName;
    };

    class Instance
    {
    public:
        static void Initialize(const InstanceSpecification &spec) { Get().InitializeImpl(spec); }

        static void Shutdown() { Get().ShutdownImpl(); }

        static bool IsValidationEnabled() { return validationEnabled; }
    private:
        VkInstance m_Instance;
    private:
        static const bool validationEnabled = true;
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