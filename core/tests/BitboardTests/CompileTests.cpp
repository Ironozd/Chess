#include <gtest/gtest.h>
#include "../../src/ChessComponents/Bitboard.h"

constexpr bool BitboardSetCompileTimeTest(){
    Chess::Bitboard board;
    board.Set(4);
    return board.Board() == (1ULL << 4);
}

static_assert(BitboardSetCompileTimeTest(), "Bitboard index was not set during compile-time.");

constexpr bool BitboardResetCompileTimeTest(){ // FIX
    Chess::Bitboard board;
    board.Set(4);
    board.Reset(4);
    return board.Board() == (0ULL << 4);
}

static_assert(BitboardResetCompileTimeTest(), "Bitboard index was not reset during compile-time.");