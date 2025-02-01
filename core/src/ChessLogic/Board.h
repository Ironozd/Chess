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
        ~Board();

        Board(const Board &other);
        Board(Board &&other) noexcept;

        /**
         * @brief Populates the board.
         * 
         * @param const FenString &fen 
         * @return true 
         * @return false 
         * 
         * @todo Incomplete
         */
        bool Populate(const FenString &fen);

        /**
         * @brief Populates a FEN string from current board.
         * 
         * @return FenString &
         */
        FenString &CreateFEN();
    private:
        BoardComponents m_Components;
    private:
        /**
         * @brief Retrieves the index of bitboard accross all 12 bitboards from provided character.
         * 
         * @param const char &character : Chess piece represented in FEN notation.
         * @return const size_t 
         * 
         * @note Does not return the reference for a full set for the purposes of performance-critical code. The bitboard should be received upon use.
         */
        const size_t RetrieveSet(const char &character) const;

        /**
         * @brief Populates 12 bitboards from the FEN string
         * 
         * @param fen 
         */
        void PopulateLayout(const FenString &fen);

        /**
         * @brief Clears all 12 bitboards.
         * 
         */
        void ClearLayout();
    };
}