#pragma once

#include "../ChessLogic/Board.h"
#include "../Window/Window.h"
#include "../Renderer/Renderer.h"

namespace Application
{
    /**
     * @brief Engine class, entry point to the Chess Engine, Renderer, Window.
     *
     * @todo Seperate both engines (Renderer, Chess)
     * 
     * @note Temporary use, however, seperated state will look similar.
     */
    class Engine
    {
    public:
        Engine();
        ~Engine();

        /**
         * @brief Runs the application and initializes window and renderer loop.
         */
        void Run();

        /**
         * @brief Shutdowns the engine.
         */
        void Shutdown();

    private:
        Chess::Board m_Board;       /** @warning Stack allocation limits use-case, only a single board object is used throughout. There is a possibility of making this std::shared_ptr or creating it when necessary instead of engine-initialization time. \todo Revise board object instantiation. */
        Renderer::Window m_Window;     /** @note Does not need to be shared, therefore for the purposes of performance-critical code, it is stack allocated. */
        Renderer::Renderer m_Renderer; /** @note Does not need to be shared, therefore for the purposes of performance-critical code, it is stack allocated. */

        bool m_Running = true;
    };
}