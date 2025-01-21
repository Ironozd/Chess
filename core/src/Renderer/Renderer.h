#pragma once
#include <memory>

namespace Chess
{
    struct Instance;

    struct RendererSpecification{
        
    };

    class Renderer
    {
    public:
        Renderer(const RendererSpecification& spec);
        ~Renderer();

        void Initialize();

        void Shutdown();
    private:
    };
}