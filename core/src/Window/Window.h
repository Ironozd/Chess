#pragma once

/** @todo Re-think, possibly change to forward declaration */
#include <string_view>
#include <vector>

/* Forward declaration for better compile-time and organization */
struct GLFWwindow;
typedef struct VkSurfaceKHR_T *VkSurfaceKHR;

namespace Renderer
{
    struct WindowSpecification
    {
        std::string_view Title;
        int Width;
        int Height;
    };
    /**
     * @brief Window class, uses GLFW library.
     */
    class Window
    {
    public:
        Window();
        ~Window();

        /**
         * @brief Initialize window with the given specification.
         *
         * @param const WindowSpecification &spec
         */
        void Initialize(const WindowSpecification &spec);
        /**
         * @brief Destroys window and shutdowns the GLFW library.
         */
        void Terminate();

        /**
         * @brief To be called each application lifetime tick.
         */
        void OnUpdate();

        /**
         * @brief Creates VkSurfaceKHR for communication with Vulkan API
         *
         * @note Vulkan is platform-agnostic, surface creation is necessary.
         */
        void CreateSurface();
        void DestroySurface();

        VkSurfaceKHR SurfaceData() { return m_Surface; }

        /* Non-member functions */
        static std::vector<const char *> GetExtensions();

    private:
        GLFWwindow *m_Window;
        VkSurfaceKHR m_Surface;
    };
}