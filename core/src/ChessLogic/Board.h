#pragma once

#include <string_view>
#include <memory>

#include "../ChessComponents/Components.h"
#include "../ChessComponents/String.h"

namespace Chess
{
    class Board
    {
    public:
        Board(const std::string_view &startFen);

        Board(const Board &other);
        Board(Board &&other);

        ~Board();

        bool Populate(const FenString &fen);

        FenString &CreateFEN();

    private:
        BoardComponents m_Components;

    private:
        const size_t RetrieveSet(const char &character) const;

        void PopulateLayout(const FenString &fen);

        void ClearLayout();
    };
}