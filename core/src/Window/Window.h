#pragma once

#include <string_view>
#include <vector>

struct GLFWwindow; // forward decl

namespace Chess
{
    struct WindowSpecification
    {
        std::string_view Title;
        size_t Width;
        size_t Height;
    };

    class Window
    {
    public:
        Window();
        ~Window();

        void Initialize(const WindowSpecification &spec);
        void Terminate();

        void OnUpdate();

        /* Non-member functions */
        static std::vector<const char*> GetExtensions();

    private:
        GLFWwindow *m_Window;
    };
}