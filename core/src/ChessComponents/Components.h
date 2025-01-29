#pragma once

#include <cstdint>
#include <string_view>

#include "Turn.h"
#include "Bitboard.h"

namespace Chess
{
    /**
     * @brief This struct holds members of Board class that are related to Chess functionality.
     * 
     * @todo Each type (except "Bitboard" m_Layout) will be changed to be represented in a bit form (e.g. WhiteKingCastleAbility = 0b0001).
     */
    struct BoardComponents
    {
        Bitboard m_Layout[12];
        Turn m_Turn;
        std::string_view m_CastleAbility;
        std::string_view m_EnPassant;
        size_t m_HalfMoves;
        size_t m_FullMoves;
    };
}