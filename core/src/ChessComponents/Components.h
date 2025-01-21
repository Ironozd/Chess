#pragma once

#include <cstdint>
#include <string_view>

#include "Turn.h"
#include "Bitboard.h"

namespace Chess
{
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