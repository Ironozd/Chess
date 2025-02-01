#pragma once
#include <memory>

namespace Renderer
{
    /* Forward declaration for better compile-time and organization */
    class Window;

    /**
     * @todo Specification behavior (holding reference of a stack allocated memory) is subject to change.
     */
    struct RendererSpecification
    {
        Window &WindowRef;

        RendererSpecification(Window &windowRef) : WindowRef(windowRef) {}
    };
    
    /**
     * @brief Renderer class, lifetime of all Vulkan objects are stored here.
     * 
     * @warning Since this class will also contain Compute API information, this class will be renamed.
     * @todo Rename the class to suit Vulkan Compute API, and re-think structure.
     */
    class Renderer
    {
    public:
        Renderer(const RendererSpecification &spec);
        ~Renderer();

        /**
         * @brief Starts the Vulkan initialization pipeline.
         * 
         * @note Currently, default behaviour, however, not fully implemented.
         */
        void Initialize();

        void Shutdown();

    private:
        RendererSpecification m_Specification;
    };
}